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
    RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(2, 1);
    config->SetStageAccess(true, true, false, false, false, true, false);
    config->SetParamAsDescriptorTable(0, 1, SHADER_VISIBILITY_PIXEL);
    config->SetRangeAsShaderResourceView(0, 0, 1, 0, 0);
    config->SetParamAsConstantBufferView(1, 0, 0, SHADER_VISIBILITY_VERTEX);
    config->SetSampler(0, TEXTURE_FILTER_MIN_MAG_MIP_LINEAR, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, 0, 1, COMPARISON_FUNC_NEVER, BORDER_COLOR_TRANSPARENT_BLACK,
      0, 0, 0, 0, SHADER_VISIBILITY_PIXEL);
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
    m_vertex_shader = Shader::LoadD3D12("render_target_to_texture_vs.cso");
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
    m_pixel_shader = Shader::LoadD3D12("render_target_to_texture_ps.cso");
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
    m_input_layout->SetNextElement(SEM_TEXCOORD, 0, R32G32_FLOAT, 0, false);
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
  Vertex_PositionTexture vertices[] =
  {
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3 (1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
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

    6, 4, 5,
    7, 4, 6,

    11, 9, 8,
    10, 9, 11,

    14, 12, 13,
    15, 12, 14,

    19, 17, 16,
    18, 17, 19,

    22, 20, 21,
    23, 20, 22
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

  // compute the bytes needed for the texture
  UINT texture_aligned_size = 0;
  try
  {
    texture_aligned_size = Texture::GetAlignedSize(graphics, RTV_TEX_WIDTH, RTV_TEX_HEIGHT, (GraphicsDataFormat)RTV_TEX_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to get texture aligned size:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  UINT constant_buffer_size = 0;
  try
  {
    constant_buffer_size = ConstantBuffer::GetAlignedSize(graphics, sizeof(XMMATRIX));
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
    m_resource_heap = BufferResourceHeap::CreateD3D12(graphics, constant_buffer_size + texture_aligned_size);
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
    m_shader_buffer_heap = ShaderResourceDescHeap::CreateD3D12(graphics, 2);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create resource descriptor heap:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the constant buffer
  try
  {
    m_constant_buffer = ConstantBuffer::CreateD3D12(graphics, *m_resource_heap, *m_shader_buffer_heap, constant_buffer_size);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create constant buffer:\n" << err.what();
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

  CreateRTV();
  DrawRTV();
}

void GameMain::UnloadContent()
{
  delete m_rtv_texture;
  delete m_depth_stencil;
  delete m_tex_heap;
  delete m_texture;
  delete m_camera;
  delete m_resource_heap;
  delete m_shader_buffer_heap;
  delete m_heap_array;
  delete m_constant_buffer;
  delete m_vert_array;
  delete m_indices;
  delete m_verts;
  delete m_vertex_shader;
  delete m_pixel_shader;
  delete m_rtv_pixel_shader;
  delete m_input_layout;
  delete m_command_list;
  delete m_rtv_pipeline;
  delete m_pipeline;
  delete m_root_sig;
}

void GameMain::Update(UINT ms)
{
  static bool resized = false;
  static bool fullscreen = false;

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
    m_constant_buffer->Upload(&wvp, 0, sizeof(wvp));

    m_command_list->SetHeapArray(*m_heap_array);
    m_command_list->SetTexture(0, *m_texture);
    m_command_list->SetConstantBuffer(1, *m_constant_buffer);

    float clear_color[4] = { .3f, .3f, .3f, 1 };
    m_command_list->PrepRenderTarget(currentRenderTarget);
    m_command_list->OMSetRenderTarget(currentRenderTarget, *m_depth_stencil);
    m_command_list->ClearRenderTarget(currentRenderTarget, clear_color);
    m_command_list->ClearDepthStencil(*m_depth_stencil, 1);

    m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
    m_command_list->IASetVertexBuffers(*m_vert_array);
    m_command_list->IASetIndexBuffer(*m_indices);

    m_command_list->DrawIndexedInstanced(m_indices->GetNumIndices(), 1, 0);

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

void GameMain::OnResize(UINT width, UINT height)
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

void GameMain::CreateRTV()
{
  GraphicsCore& graphics = GetGraphics();

  try
  {
    m_rtv_pixel_shader = Shader::LoadD3D12("render_target_to_texture_gen_texture_ps.cso");
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to load secondary pixel shader:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  
  try
  {
    RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
    rtv_config->SetAlphaToCoverageEnable(false);
    rtv_config->SetIndependentBlendEnable(false);
    rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
    m_rtv_pipeline = Pipeline::CreateD3D12(graphics, *m_input_layout, TOPOLOGY_TRIANGLE, *m_vertex_shader, *m_rtv_pixel_shader, DEPTH_FUNC_LESS_EQUAL, *rtv_config, *m_root_sig);
    delete rtv_config;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create pipeline:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the texture
  try
  {
    UINT texture_aligned_size = Texture::GetAlignedSize(graphics, RTV_TEX_WIDTH, RTV_TEX_HEIGHT, (GraphicsDataFormat)RTV_TEX_FORMAT);
    m_tex_heap = TextureResourceHeap::CreateD3D12(graphics, texture_aligned_size);
    m_texture = Texture::CreateD3D12_2D(graphics, *m_tex_heap, *m_shader_buffer_heap, RTV_TEX_WIDTH, RTV_TEX_HEIGHT, (GraphicsDataFormat)RTV_TEX_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture to copy render target to:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    vector<RenderTarget::Config> configs;
    configs.push_back({ RTV_TEX_WIDTH, RTV_TEX_HEIGHT, (GraphicsDataFormat)RTV_TEX_FORMAT });
    vector<RenderTarget*> render_targets;
    RenderTarget::CreateD3D12(graphics, configs, render_targets);
    m_rtv_texture = render_targets[0];
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create custom render target:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void GameMain::DrawRTV()
{
  try
  {
    GraphicsCore& graphics = GetGraphics();

    m_command_list->Close();
    m_command_list->Reset(m_rtv_pipeline);

    Viewport viewport = graphics.GetDefaultViewport();
    viewport.width = RTV_TEX_WIDTH;
    viewport.height = RTV_TEX_HEIGHT;
    viewport.top_left_x = 0;
    viewport.top_left_y = 0;

    RECT scissor_rect = ViewportToScissorRect(viewport);

    m_command_list->SetRootSignature(*m_root_sig);
    m_command_list->RSSetViewport(viewport);
    m_command_list->RSSetScissorRect(scissor_rect);

    Camera* camera = new Camera(RTV_TEX_WIDTH / (float)RTV_TEX_HEIGHT, 0.01f, 100.0f, XMFLOAT4(0, 0, -2, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));

    // upload the wvp matrix for the camera to the constant buffer
    XMMATRIX tmp;
    XMMATRIX wvp = XMMatrixIdentity();
    camera->GetView(tmp);
    wvp *= tmp;
    camera->GetProjection(tmp);
    wvp *= tmp;
    wvp = XMMatrixTranspose(wvp);
    m_constant_buffer->Upload(&wvp, 0, sizeof(wvp));

    m_command_list->SetHeapArray(*m_heap_array);
    m_command_list->SetTexture(0, *m_texture);
    m_command_list->SetConstantBuffer(1, *m_constant_buffer);

    float clear_color[4] = { 0, 0, 0, 1 };
    m_command_list->PrepRenderTarget(*m_rtv_texture);
    m_command_list->OMSetRenderTarget(*m_rtv_texture, *m_depth_stencil);
    m_command_list->ClearRenderTarget(*m_rtv_texture, clear_color);
    m_command_list->ClearDepthStencil(*m_depth_stencil, 1);

    m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
    m_command_list->IASetVertexBuffers(*m_vert_array);
    m_command_list->IASetIndexBuffer(*m_indices);

    m_command_list->DrawIndexedInstanced(m_indices->GetNumIndices(), 1, 0);

    m_command_list->RenderTargetToPresent(*m_rtv_texture);

    m_command_list->Close();
    graphics.ExecuteCommandList(*m_command_list);
    graphics.WaitOnFence();

    // move the render target image to the texture used in normal rendering
    m_command_list->Reset(m_rtv_pipeline);
    m_rtv_texture->PrepUpload(graphics, *m_command_list, *m_texture);
    m_command_list->Close();
    graphics.ExecuteCommandList(*m_command_list);
    graphics.WaitOnFence();

    delete camera;
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to draw to custom render target and copy to texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}
