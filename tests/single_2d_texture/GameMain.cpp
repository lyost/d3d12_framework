#include "GameMain.h"
#include <directxmath.h>
#include "Graphics/RootSignatureConfig.h"
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RenderTargetViewFormats.h"
#include "Graphics/VertexDeclarations/Vertex_PositionColor.h"
using namespace DirectX;
using namespace std;

const UINT tex_width = 256;
const UINT tex_height = 256;

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

  RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(1, 1);
  config->SetStageAccess(true, true, false, false, false, true, false);
  config->SetParamAsDescriptorTable(0, 1, SHADER_VISIBILITY_PIXEL);
  config->SetRangeAsShaderResourceView(0, 0, 1, 0, 0);
  config->SetSampler(0, TEXTURE_FILTER_MIN_MAG_MIP_LINEAR, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, 0, 1, COMPARISON_FUNC_NEVER, BORDER_COLOR_TRANSPARENT_BLACK,
    0, 0, 0, 0, SHADER_VISIBILITY_PIXEL);
  m_root_sig = RootSignature::CreateD3D12(graphics, *config);
  if (m_root_sig == NULL)
  {
    exit(1);
  }

  m_vertex_shader = Shader::LoadD3D12("single_2d_texture_vs.cso");
  if (m_vertex_shader == NULL)
  {
    exit(1);
  }
  m_pixel_shader = Shader::LoadD3D12("single_2d_texture_ps.cso");
  if (m_pixel_shader == NULL)
  {
    exit(1);
  }

  m_input_layout = InputLayout::CreateD3D12(2);
  m_input_layout->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
  m_input_layout->SetNextElement(SEM_TEXCOORD, 0, R32G32_FLOAT, 0, false);

  RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
  rtv_config->SetAlphaToCoverageEnable(false);
  rtv_config->SetIndependentBlendEnable(false);
  rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
  m_pipeline = Pipeline::CreateD3D12(graphics, *m_input_layout, TOPOLOGY_TRIANGLE, *m_vertex_shader, *m_pixel_shader, *rtv_config, *m_root_sig);
  if (m_pipeline == NULL)
  {
    exit(1);
  }

  m_command_list = CommandList::CreateD3D12Direct(graphics, m_pipeline);

  // create the scissor rect that matches the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_PositionTexture vertices[] =
  {
    { XMFLOAT3( 0.0f,   0.25f * aspect_ratio, 0.0f), XMFLOAT2(0.5f, 0.0f) },
    { XMFLOAT3( 0.25f, -0.25f * aspect_ratio, 0.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-0.25f, -0.25f * aspect_ratio, 0.0f), XMFLOAT2(0.0f, 1.0f) },
  };
  m_verts = VertexBuffer_PositionTexture::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
  if (m_verts == NULL)
  {
    exit(1);
  }

  // combine the vertex and instance buffer
  m_vert_array = VertexBufferArray::CreateD3D12(1);
  m_vert_array->Set(0, *m_verts);

  // create the texture
  UINT texture_aligned_size = Texture::GetAlignedSize(graphics, tex_width, tex_height, R8B8G8A8_UNORM);
  m_shader_buffer_heap = ShaderResourceDescHeap::CreateD3D12(graphics, 1);
  if (m_shader_buffer_heap == NULL)
  {
    exit(1);
  }
  m_tex_heap = TextureResourceHeap::CreateD3D12(graphics, texture_aligned_size);
  if (m_tex_heap == NULL)
  {
    exit(1);
  }
  m_texture = Texture::CreateD3D12_2D(graphics, *m_tex_heap, *m_shader_buffer_heap, tex_width, tex_height, R8B8G8A8_UNORM);
  if (m_texture == NULL)
  {
    exit(1);
  }
  const UINT64 upload_buffer_size = m_texture->GetUploadBufferSize();
  m_upload_heap = BufferResourceHeap::CreateD3D12(graphics, upload_buffer_size);
  if (m_upload_heap == NULL)
  {
    exit(1);
  }
  m_upload_texture = TextureUploadBuffer::CreateD3D12(graphics, *m_texture, *m_upload_heap);
  if (m_upload_texture == NULL)
  {
    exit(1);
  }
  vector<UINT8> tex_bytes;
  CreateTextureImage(tex_bytes);
  m_upload_texture->PrepUpload(graphics, *m_command_list, *m_texture, tex_bytes);

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
  delete m_heap_array;
  delete m_upload_texture;
  delete m_texture;
  delete m_upload_heap;
  delete m_tex_heap;
  delete m_shader_buffer_heap;
  delete m_vert_array;
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
  Window& window = GetWindow();
  const KeyboardState& keyboard = window.GetKeyboardState();
  if (keyboard.IsKeyDown(VK_ESCAPE,false))
  {
    Exit();
  }
}

void GameMain::Draw(UINT ms)
{
  GraphicsCore& graphics = GetGraphics();
  const RenderTarget& currentRenderTarget = graphics.GetBackBuffer().GetCurrentRenderTarget();
  m_command_list->Reset(m_pipeline);
  m_command_list->SetRootSignature(*m_root_sig);
  m_command_list->SetHeapArray(*m_heap_array);
  m_command_list->SetTexture(0, *m_texture);
  m_command_list->RSSetViewport(graphics.GetDefaultViewport());
  m_command_list->RSSetScissorRect(m_scissor_rect);

  float clear_color[4] = { .3f, .3f, .3f, 1 };
  m_command_list->PrepRenderTarget(currentRenderTarget);
  m_command_list->OMSetRenderTarget(currentRenderTarget);
  m_command_list->ClearRenderTarget(currentRenderTarget, clear_color);

  m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
  m_command_list->IASetVertexBuffers(*m_vert_array);

  m_command_list->DrawInstanced(m_verts->GetNumVertices(), 1, 0);

  m_command_list->RenderTargetToPresent(currentRenderTarget);
  m_command_list->Close();
  
  graphics.ExecuteCommandList(*m_command_list);

  graphics.Swap();
}

void GameMain::OnResize(UINT width,UINT height)
{
  Game::OnResize(width,height);

  GraphicsCore& graphics = GetGraphics();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());
}

void GameMain::CreateTextureImage(std::vector<UINT8>& bytes) const
{
  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture
  const UINT tex_size = tex_width * tex_height * bytes_per_pixel;
  bytes.resize(tex_size);
  for (UINT byte_index = 0; byte_index < tex_size; byte_index += bytes_per_pixel)
  {
    bytes[byte_index] = 0;
    bytes[byte_index + 1] = 255;
    bytes[byte_index + 2] = 0;
    bytes[byte_index + 3] = 255;
  }
}
