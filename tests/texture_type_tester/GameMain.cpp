#include <sstream>
#include <cmath>
#include "GameMain.h"
#include <directxmath.h>
#include "Graphics/RootSignatureConfig.h"
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RenderTargetViewFormats.h"
#include "Graphics/VertexDeclarations/Vertex_PositionTexture.h"
#include "Graphics/DepthEnums.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

GameMain::GameMain(WCHAR* title)
:Game(title)
{
}

GameMain::~GameMain()
{
}

void GameMain::LoadContent()
{
  GraphicsCore& graphics = GetGraphics();

  try
  {
    RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(3, 1);
    config->SetStageAccess(true, true, false, false, false, true, false);
    config->SetParamAsDescriptorTable(0, 3, SHADER_VISIBILITY_PIXEL);
    config->SetRangeAsShaderResourceView(0, 0, 1, 0, 0);
    config->SetRangeAsShaderResourceView(0, 1, 1, 1, 0);
    config->SetRangeAsShaderResourceView(0, 2, 1, 2, 0);
    config->SetParamAsConstantBufferView(1, 0, 0, SHADER_VISIBILITY_VERTEX);
    config->SetParamAsConstantBufferView(2, 1, 0, SHADER_VISIBILITY_PIXEL);
    config->SetSampler(0, TEXTURE_FILTER_MIN_MAG_MIP_LINEAR, TEXTURE_ADDRESS_MODE_CLAMP, TEXTURE_ADDRESS_MODE_CLAMP, TEXTURE_ADDRESS_MODE_CLAMP, 0, 1, COMPARISON_FUNC_NEVER,
      BORDER_COLOR_TRANSPARENT_BLACK, 0, 0, 0, 0, SHADER_VISIBILITY_PIXEL);
    m_root_sig = RootSignature::CreateD3D12(graphics, *config);
    delete config;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create root signature:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    m_vertex_shader = Shader::LoadD3D12("texture_type_tester_vs.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load vertex shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_pixel_shader = Shader::LoadD3D12("texture_type_tester_ps.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load pixel shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    m_input_layout = InputLayout::CreateD3D12(2);
    m_input_layout->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
    m_input_layout->SetNextElement(SEM_TEXCOORD, 0, R32G32B32_FLOAT, 0, false);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create input layout:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
    rtv_config->SetAlphaToCoverageEnable(false);
    rtv_config->SetIndependentBlendEnable(false);
    rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
    m_pipeline = Pipeline::CreateD3D12(graphics, *m_input_layout, TOPOLOGY_TRIANGLE, *m_vertex_shader, *m_pixel_shader, DEPTH_FUNC_LESS_EQUAL, *rtv_config, *m_root_sig);
    delete rtv_config;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create pipeline:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  try
  {
    m_command_list = CommandList::CreateD3D12Direct(graphics, m_pipeline);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create command list:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the scissor rect that matches the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  // setup the cameras for the viewport
  m_camera_angle = 3 * XM_PI / 2;
  m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));

  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_PositionTextureUVW vertices[] =
  {
    { XMFLOAT3(-1.0f,-1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
  };
  try
  {
    m_verts = VertexBuffer_PositionTexture::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the index buffer
  WORD indices[] =
  {
    3, 1, 0,
    2, 1, 3,
  };
  try
  {
    m_indices = IndexBuffer16::CreateD3D12(graphics, ARRAYSIZE(indices), indices);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create index buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // combine the vertex and instance buffer
  try
  {
    m_vert_array = VertexBufferArray::CreateD3D12(1);
    m_vert_array->Set(0, *m_verts);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // calculate the space needed for the textures
  UINT texture_aligned_size = 0;
  try
  {
    texture_aligned_size += Texture1D::GetAlignedSize(graphics, TEXTURE_WIDTH, (GraphicsDataFormat)TEXTURE_FORMAT);
    texture_aligned_size += Texture2D::GetAlignedSize(graphics, TEXTURE_WIDTH, TEXTURE_HEIGHT, (GraphicsDataFormat)TEXTURE_FORMAT);
    texture_aligned_size += Texture3D::GetAlignedSize(graphics, TEXTURE_WIDTH, TEXTURE_HEIGHT, TEXTURE_DEPTH, (GraphicsDataFormat)TEXTURE_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to get texture aligned size:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // calculate the space needed for the constant buffers
  UINT constant_buffer_size_vs = 0;
  UINT constant_buffer_size_ps = 0;
  try
  {
    constant_buffer_size_vs = ConstantBuffer::GetAlignedSize(graphics, sizeof(XMMATRIX));
    constant_buffer_size_ps = ConstantBuffer::GetAlignedSize(graphics, sizeof(m_current_mode));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to get constant buffer aligned size:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the resource heap
  try
  {
    m_resource_heap = BufferResourceHeap::CreateD3D12(graphics, constant_buffer_size_vs + constant_buffer_size_ps + texture_aligned_size);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create buffer resource heap:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the descriptor heap
  try
  {
    m_shader_buffer_heap = ShaderResourceDescHeap::CreateD3D12(graphics, 5);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create resource descriptor heap:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the constant buffers
  try
  {
    m_constant_buffer_vs = ConstantBuffer::CreateD3D12(graphics, *m_resource_heap, *m_shader_buffer_heap, constant_buffer_size_vs);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create constant buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_constant_buffer_ps = ConstantBuffer::CreateD3D12(graphics, *m_resource_heap, *m_shader_buffer_heap, constant_buffer_size_ps);
    m_current_mode = TEXTURE_MODE_1D;
    m_constant_buffer_ps->Upload(&m_current_mode, 0, sizeof(m_current_mode));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create constant buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the textures
  try
  {
    m_tex_heap = TextureResourceHeap::CreateD3D12(graphics, texture_aligned_size);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture resource heap:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_texture1d = Texture1D::CreateD3D12(graphics, *m_tex_heap, *m_shader_buffer_heap, TEXTURE_WIDTH, (GraphicsDataFormat)TEXTURE_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 1D:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_texture2d = Texture2D::CreateD3D12(graphics, *m_tex_heap, *m_shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, (GraphicsDataFormat)TEXTURE_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 2D:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_texture3d = Texture3D::CreateD3D12(graphics, *m_tex_heap, *m_shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, TEXTURE_DEPTH, (GraphicsDataFormat)TEXTURE_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 3D:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the buffer for uploading the textures (will reuse the same buffer, so pick the largest texture)
  const UINT64 upload_buffer_size = m_texture3d->GetUploadBufferSize();
  try
  {
    m_upload_heap = BufferResourceHeap::CreateD3D12(graphics, upload_buffer_size);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture upload heap:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_upload_texture = TextureUploadBuffer::CreateD3D12(graphics, *m_texture3d, *m_upload_heap);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture upload buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  
  CreateDepthStencil();

  // create the heap array
  try
  {
    m_heap_array = HeapArray::CreateD3D12(1);
    m_heap_array->SetHeap(0, *m_shader_buffer_heap);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create heap array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // upload the textures
  try
  {
    vector<UINT8> tex_bytes;
    CreateTexture1D(tex_bytes);
    m_upload_texture->PrepUpload(graphics, *m_command_list, *m_texture1d, tex_bytes);
    m_command_list->Close();
    graphics.ExecuteCommandList(*m_command_list);
    graphics.WaitOnFence();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    vector<UINT8> tex_bytes;
    CreateTexture2D(tex_bytes);
    m_command_list->Reset(m_pipeline);
    m_upload_texture->PrepUpload(graphics, *m_command_list, *m_texture2d, tex_bytes);
    m_command_list->Close();
    graphics.ExecuteCommandList(*m_command_list);
    graphics.WaitOnFence();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    vector<UINT8> tex_bytes;
    CreateTexture3D(tex_bytes);
    m_command_list->Reset(m_pipeline);
    m_upload_texture->PrepUpload(graphics, *m_command_list, *m_texture3d, tex_bytes);
    m_command_list->Close();
    graphics.ExecuteCommandList(*m_command_list);
    graphics.WaitOnFence();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void GameMain::UnloadContent()
{
  delete m_depth_stencil;
  delete m_tex_heap;
  delete m_upload_heap;
  delete m_texture1d;
  delete m_texture2d;
  delete m_texture3d;
  delete m_upload_texture;
  delete m_camera;
  delete m_resource_heap;
  delete m_shader_buffer_heap;
  delete m_heap_array;
  delete m_constant_buffer_vs;
  delete m_constant_buffer_ps;
  delete m_vert_array;
  delete m_indices;
  delete m_verts;
  delete m_vertex_shader;
  delete m_pixel_shader;
  delete m_input_layout;
  delete m_command_list;
  delete m_pipeline;
  delete m_root_sig;
}

void GameMain::Update(UINT ms)
{
  static bool resized = false;
  static bool fullscreen = false;
  static bool spacebar_down = false;

  try
  {
    Window& window = GetWindow();
    const KeyboardState& keyboard = window.GetKeyboardState();
    if (keyboard.IsKeyDown(VK_ESCAPE, false))
    {
      Exit();
    }
    else if (keyboard.IsKeyDown(VK_LEFT, true))
    {
      m_camera_angle -= XM_PI * ms / 1000.0f; // todo: bounds
      UpdateCamera();
    }
    else if (keyboard.IsKeyDown(VK_RIGHT, true))
    {
      m_camera_angle += XM_PI * ms / 1000.0f; // todo: bounds
      UpdateCamera();
    }
    else if (keyboard.IsKeyDown(VK_F1, false) && !resized)
    {
      window.Resize(1024, 768);
      resized = true;
    }
    else if (keyboard.IsKeyDown(VK_F2, false) && !fullscreen)
    {
      // enter full screen mode
      Fullscreen(true);
      fullscreen = true;
    }
    else if (keyboard.IsKeyDown(VK_F3, false) && fullscreen)
    {
      // return to window mode
      Fullscreen(false);
      fullscreen = false;
    }
    else if (keyboard.IsKeyDown(VK_OEM_4, false))
    {
      window.ShowMousePointer(false);
    }
    else if (keyboard.IsKeyDown(VK_OEM_6, false))
    {
      window.ShowMousePointer(true);
    }
    else if (keyboard.IsKeyDown('9', false))
    {
      window.ConstrainMousePointer(true);
    }
    else if (keyboard.IsKeyDown('0', false))
    {
      window.ConstrainMousePointer(false);
    }
    else if (keyboard.IsKeyDown(VK_SPACE, false))
    {
      spacebar_down = true;
    }
    else if (spacebar_down)
    {
      spacebar_down = false;

      m_current_mode = (m_current_mode + 1) % TEXTURE_MODE_MAX;
      m_constant_buffer_ps->Upload(&m_current_mode, 0, sizeof(m_current_mode));
    }
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to complete update:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void GameMain::Draw(UINT ms)
{
  try
  {
    GraphicsCore& graphics = GetGraphics();
    const RenderTarget& currentRenderTarget = graphics.GetBackBuffer().GetCurrentRenderTarget();
    m_command_list->Reset(m_pipeline);
    m_command_list->SetRootSignature(*m_root_sig);
    m_command_list->RSSetViewport(graphics.GetDefaultViewport());
    m_command_list->RSSetScissorRect(m_scissor_rect);

    // upload the wvp matrix for the camera to the constant buffer
    XMMATRIX tmp;
    XMMATRIX wvp = XMMatrixIdentity();
    m_camera->GetView(tmp);
    wvp *= tmp;
    m_camera->GetProjection(tmp);
    wvp *= tmp;
    wvp = XMMatrixTranspose(wvp);
    m_constant_buffer_vs->Upload(&wvp, 0, sizeof(wvp));

    m_command_list->SetHeapArray(*m_heap_array);
    m_command_list->SetTexture(0, *m_texture1d); // note: only binding the first texture in its descriptor heap to the slot since the others need to be contiguous after it
    m_command_list->SetConstantBuffer(1, *m_constant_buffer_vs);
    m_command_list->SetConstantBuffer(2, *m_constant_buffer_ps);

    float clear_color[4] = { .3f, .3f, .3f, 1 };
    m_command_list->PrepRenderTarget(currentRenderTarget);
    m_command_list->OMSetRenderTarget(currentRenderTarget, *m_depth_stencil);
    m_command_list->ClearRenderTarget(currentRenderTarget, clear_color);
    m_command_list->ClearDepthStencil(*m_depth_stencil, 1);

    m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
    m_command_list->IASetVertexBuffers(*m_vert_array);
    m_command_list->IASetIndexBuffer(*m_indices);

    m_command_list->DrawIndexedInstanced(m_indices->GetNumIndices(), 2, 0);

    m_command_list->RenderTargetToPresent(currentRenderTarget);
    m_command_list->Close();

    graphics.ExecuteCommandList(*m_command_list);

    graphics.Swap();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to draw frame:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void GameMain::OnResize(UINT width,UINT height)
{
  try
  {
    Game::OnResize(width, height);

    GraphicsCore& graphics = GetGraphics();
    const Viewport& full_viewport = graphics.GetDefaultViewport();
    m_scissor_rect = ViewportToScissorRect(full_viewport);

    delete m_camera;
    m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));
    UpdateCamera();

    delete m_depth_stencil;
    CreateDepthStencil();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to resize:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void GameMain::CreateTexture1D(std::vector<UINT8>& bytes)
{
  UINT               width  = 64;
  GraphicsDataFormat format = R8B8G8A8_UNORM;

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT tex_size = width * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
  {
    const float percent = x / (float)width;
    bytes[byte_index] = (UINT8)(255 * (1 - percent));
    bytes[byte_index + 1] = 0;
    bytes[byte_index + 2] = (UINT8)(255 * percent);
    bytes[byte_index + 3] = 255;
  }
}

void GameMain::CreateTexture2D(std::vector<UINT8>& bytes)
{
  UINT               width  = 64;
  UINT               height = 64;
  GraphicsDataFormat format = R8B8G8A8_UNORM;

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT center_x = width / 2;
  const UINT center_y = height / 2;
  const UINT radius_sq = center_x * center_x;

  const UINT tex_size = width * height * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT y = 0; y < height; y++)
  {
    for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
    {
      const float dx = x + .5f - center_x;
      const float dy = y + .5f - center_y;
      const float dist_sq = dx * dx + dy * dy;

      if (dist_sq > radius_sq)
      {
        bytes[byte_index] = 0;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = 0;
        bytes[byte_index + 3] = 255;
      }
      else if (dy >= 0)
      {
        bytes[byte_index] = 255;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = 0;
        bytes[byte_index + 3] = 255;
      }
      else if (dx < 0)
      {
        bytes[byte_index] = 0;
        bytes[byte_index + 1] = 255;
        bytes[byte_index + 2] = 0;
        bytes[byte_index + 3] = 255;
      }
      else
      {
        bytes[byte_index] = 0;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = 255;
        bytes[byte_index + 3] = 255;
      }
    }
  }
}

void GameMain::CreateTexture3D(std::vector<UINT8>& bytes)
{
  UINT               width  = 64;
  UINT               height = 64;
  UINT16             depth  = 3;
  GraphicsDataFormat format = R8B8G8A8_UNORM;

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT center_x = width / 2;
  const UINT center_y = height / 2;
  const UINT radius_sq = center_x * center_x;

  const UINT tex_size = width * height * depth * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT z = 0; z < depth; z++)
  {
    for (UINT y = 0; y < height; y++)
    {
      for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
      {
        bytes[byte_index]     = (z == 0) ? 255 : 0;
        bytes[byte_index + 1] = (z == 1) ? 255 : 0;
        bytes[byte_index + 2] = (z == 2) ? 255 : 0;
        bytes[byte_index + 3] = 255;
      }
    }
  }
}

void GameMain::UpdateCamera()
{
  const float orbit_dist = 10;

  XMFLOAT4 pos(orbit_dist * cos(m_camera_angle), 0, orbit_dist * sin(m_camera_angle), 1);
  XMFLOAT4 dir;
  XMFLOAT4 up(0, 1, 0, 0);

  XMFLOAT4 origin(0, 0, 0, 1);
  XMVECTOR pos_vector = XMLoadFloat4(&pos);
  XMVECTOR origin_vector = XMLoadFloat4(&origin);
  XMVECTOR dir_vector = origin_vector - pos_vector;
  XMVector4Normalize(dir_vector);
  XMStoreFloat4(&dir, dir_vector);

  m_camera->SetView(pos, dir, up);
}

void GameMain::CreateDepthStencil()
{
  GraphicsCore& graphics = GetGraphics();
  Viewport full_viewport = graphics.GetDefaultViewport();

  vector<DepthStencil::Config> configs;
  vector<DepthStencil*> depth_stencils;
  configs.push_back({ (UINT)full_viewport.width, (UINT)full_viewport.height, 1 });
  try
  {
    DepthStencil::CreateD3D12(graphics, configs, depth_stencils);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create depth stencil:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  m_depth_stencil = depth_stencils[0];
}