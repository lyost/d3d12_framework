#include <cmath>
#include "GameMain.h"
#include <directxmath.h>
#include "Graphics/RootSignatureConfig.h"
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RenderTargetViewFormats.h"
#include "Graphics/VertexDeclarations/Vertex_PositionTexture.h"
#include "Graphics/DepthEnums.h"
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

  RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(1, 0);
  config->SetStageAccess(true, true, true, true, false, true, false);
  config->SetParamAsConstantBufferView(0, 0, 0, SHADER_VISIBILITY_DOMAIN);
  m_root_sig = RootSignature::CreateD3D12(graphics, *config);
  if (m_root_sig == NULL)
  {
    exit(1);
  }

  m_vertex_shader = Shader::LoadD3D12("hull_and_domain_vs.cso");
  if (m_vertex_shader == NULL)
  {
    exit(1);
  }
  m_hull_shader = Shader::LoadD3D12("hull_and_domain_hs.cso");
  if (m_hull_shader == NULL)
  {
    exit(1);
  }
  m_domain_shader = Shader::LoadD3D12("hull_and_domain_ds.cso");
  if (m_domain_shader == NULL)
  {
    exit(1);
  }
  m_pixel_shader = Shader::LoadD3D12("hull_and_domain_ps.cso");
  if (m_pixel_shader == NULL)
  {
    exit(1);
  }

  m_input_layout = InputLayout::CreateD3D12(1);
  m_input_layout->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);

  RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
  rtv_config->SetAlphaToCoverageEnable(false);
  rtv_config->SetIndependentBlendEnable(false);
  rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
  m_pipeline = Pipeline::CreateD3D12(graphics, *m_input_layout, TOPOLOGY_PATCH, *m_vertex_shader, *m_hull_shader, *m_domain_shader, *m_pixel_shader, DEPTH_FUNC_LESS_EQUAL, *rtv_config, *m_root_sig,
    true);
  if (m_pipeline == NULL)
  {
    exit(1);
  }

  m_command_list = CommandList::CreateD3D12Direct(graphics, m_pipeline);

  // create the scissor rect that matches the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  // setup the cameras for the viewport
  m_camera_angle = 3 * XM_PI / 2;
  m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));

  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_Position vertices[] =
  {
    { XMFLOAT3(-3.0f, -3.0f, 0) },
    { XMFLOAT3( 3.0f, -3.0f, 0) },
    { XMFLOAT3( 3.0f,  3.0f, 0) },
    { XMFLOAT3(-3.0f,  3.0f, 0) },
  };
  m_verts = VertexBuffer_Position::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
  if (m_verts == NULL)
  {
    exit(1);
  }

  // create the index buffer
  WORD indices[] =
  {
    0, 1, 2, 3,
  };
  m_indices = IndexBuffer16::CreateD3D12(graphics, ARRAYSIZE(indices), indices);
  if (m_indices == NULL)
  {
    exit(1);
  }

  m_vert_array = VertexBufferArray::CreateD3D12(1);
  m_vert_array->Set(0, *m_verts);

  // create the resource heap
  UINT constant_buffer_size = ConstantBuffer::GetAlignedSize(graphics, sizeof(XMMATRIX));
  m_resource_heap = BufferResourceHeap::CreateD3D12(graphics, constant_buffer_size);
  if (m_resource_heap == NULL)
  {
    exit(1);
  }

  // create the descriptor heap
  m_shader_buffer_heap = ShaderResourceDescHeap::CreateD3D12(graphics, 1);
  if (m_shader_buffer_heap == NULL)
  {
    exit(1);
  }

  // create the constant buffer
  m_constant_buffer = ConstantBuffer::CreateD3D12(graphics, *m_resource_heap, *m_shader_buffer_heap, constant_buffer_size);
  if (m_constant_buffer == NULL)
  {
    exit(1);
  }
  
  CreateDepthStencil();

  // create the heap array
  m_heap_array = HeapArray::CreateD3D12(1);
  m_heap_array->SetHeap(0, *m_shader_buffer_heap);

  // finish uploading the textures
  m_command_list->Close();
  graphics.ExecuteCommandList(*m_command_list);
  graphics.WaitOnFence();
}

void GameMain::UnloadContent()
{
  delete m_depth_stencil;
  delete m_camera;
  delete m_resource_heap;
  delete m_shader_buffer_heap;
  delete m_heap_array;
  delete m_constant_buffer;
  delete m_vert_array;
  delete m_indices;
  delete m_verts;
  delete m_vertex_shader;
  delete m_hull_shader;
  delete m_domain_shader;
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

void GameMain::Draw(UINT ms)
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
  m_command_list->SetConstantBuffer(0, *m_constant_buffer);

  float clear_color[4] = { .3f, .3f, .3f, 1 };
  m_command_list->PrepRenderTarget(currentRenderTarget);
  m_command_list->OMSetRenderTarget(currentRenderTarget, *m_depth_stencil);
  m_command_list->ClearRenderTarget(currentRenderTarget, clear_color);
  m_command_list->ClearDepthStencil(*m_depth_stencil, 1);

  m_command_list->IASetTopology(IA_TOPOLOGY_4_CONTROL_POINT_PATCH);
  m_command_list->IASetVertexBuffers(*m_vert_array);
  m_command_list->IASetIndexBuffer(*m_indices);
  
  m_command_list->DrawIndexedInstanced(m_indices->GetNumIndices(), 1, 0);

  m_command_list->RenderTargetToPresent(currentRenderTarget);
  m_command_list->Close();
  
  graphics.ExecuteCommandList(*m_command_list);

  graphics.Swap();
}

void GameMain::OnResize(UINT width,UINT height)
{
  Game::OnResize(width,height);

  GraphicsCore& graphics = GetGraphics();
  const Viewport& full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(full_viewport);

  delete m_camera;
  m_camera = new Camera(full_viewport.width / full_viewport.height, 0.01f, 100.0f, XMFLOAT4(0, 0, -10, 1), XMFLOAT4(0, 0, 1, 0), XMFLOAT4(0, 1, 0, 0));
  UpdateCamera();

  delete m_depth_stencil;
  CreateDepthStencil();
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
  DepthStencil::CreateD3D12(graphics, configs, depth_stencils);
  m_depth_stencil = depth_stencils[0];
}
