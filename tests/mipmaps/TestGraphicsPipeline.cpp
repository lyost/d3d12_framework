#include <sstream>
#include <directxmath.h>
#include "TestGraphicsPipeline.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

TestGraphicsPipeline::TestGraphicsPipeline(GraphicsCore& graphics)
:m_model(NULL),
 m_camera(NULL)
{
  try
  {
    RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(3, 2);
    config->SetStageAccess(true, true, false, false, false, true, false);
    config->SetParamAsDescriptorTable(0, 7, SHADER_VISIBILITY_PIXEL);
    config->SetRangeAsShaderResourceView(0, 0, 1, 0, 0);
    config->SetRangeAsShaderResourceView(0, 1, 1, 1, 0);
    config->SetRangeAsShaderResourceView(0, 2, 1, 2, 0);
    config->SetRangeAsShaderResourceView(0, 3, 1, 3, 0);
    config->SetRangeAsShaderResourceView(0, 4, 1, 4, 0);
    config->SetRangeAsShaderResourceView(0, 5, 1, 5, 0);
    config->SetRangeAsShaderResourceView(0, 6, 1, 6, 0);
    config->SetParamAsConstantBufferView(1, 0, 0, SHADER_VISIBILITY_VERTEX);
    config->SetParamAsConstantBufferView(2, 1, 0, SHADER_VISIBILITY_PIXEL);
    config->SetSampler(0, TEXTURE_FILTER_MIN_MAG_MIP_LINEAR, TEXTURE_ADDRESS_MODE_CLAMP, TEXTURE_ADDRESS_MODE_CLAMP, TEXTURE_ADDRESS_MODE_CLAMP, 0, 1, COMPARISON_FUNC_NEVER,
      BORDER_COLOR_TRANSPARENT_BLACK, 0, 0, 0, 0, SHADER_VISIBILITY_PIXEL);
    config->SetSampler(1, TEXTURE_FILTER_MIN_MAG_MIP_LINEAR, TEXTURE_ADDRESS_MODE_CLAMP, TEXTURE_ADDRESS_MODE_CLAMP, TEXTURE_ADDRESS_MODE_CLAMP, 0, 1, COMPARISON_FUNC_NEVER,
      BORDER_COLOR_TRANSPARENT_BLACK, 1, 1, 1, 0, SHADER_VISIBILITY_PIXEL);
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

  Shader* vertex_shader;
  Shader* pixel_shader;
  InputLayout* input_layout;
  try
  {
    vertex_shader = Shader::LoadD3D12("mipmaps_vs.cso");
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
    pixel_shader = Shader::LoadD3D12("mipmaps_ps.cso");
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
    input_layout = InputLayout::CreateD3D12(3);
    input_layout->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
    input_layout->SetNextElement(SEM_TEXCOORD, 0, R32G32B32_FLOAT, 0, false);
    input_layout->SetNextElement(SEM_TEXCOORD, 1, R32G32B32_FLOAT, 1, true, 1);
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
    DepthStencilConfig ds_config;
    ds_config.depth_enable        = true;
    ds_config.stencil_enable      = false;
    ds_config.dsv_format          = D32_FLOAT;
    ds_config.depth_write_enabled = true;
    ds_config.depth_comparison    = COMPARISON_FUNC_LESS_EQUAL;
    RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
    rtv_config->SetAlphaToCoverageEnable(false);
    rtv_config->SetIndependentBlendEnable(false);
    rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
    m_pipeline = Pipeline::CreateD3D12(graphics, *input_layout, TOPOLOGY_TRIANGLE, *vertex_shader, NULL, *pixel_shader, &ds_config, *rtv_config, *m_root_sig);
    delete rtv_config;
    delete input_layout;
    delete pixel_shader;
    delete vertex_shader;
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

  // create the instance buffer
  XMFLOAT3 instance_pos[] =
  {
    XMFLOAT3(-2, 0, 0),
    XMFLOAT3( 2, 0, 0),
  };
  try
  {
    m_instance = VertexBuffer_Custom::CreateD3D12(graphics, sizeof(instance_pos) / sizeof(XMFLOAT3), sizeof(XMFLOAT3), instance_pos);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create instance buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the descriptor heap
  try
  {
    m_shader_buffer_heap = ShaderResourceDescHeap::CreateD3D12(graphics, 9);
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
    m_constant_buffer_vs = ConstantBuffer::CreateD3D12(graphics, *m_shader_buffer_heap, sizeof(XMMATRIX));
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
    m_constant_buffer_ps = ConstantBuffer::CreateD3D12(graphics, *m_shader_buffer_heap, sizeof(m_current_mode) + sizeof(m_current_mipmap_level));
    m_current_mode = TEXTURE_MODE_1D;
    m_current_mipmap_level = 0;
    m_constant_buffer_ps->Upload(&m_current_mode, 0, sizeof(m_current_mode));
    m_constant_buffer_ps->Upload(&m_current_mipmap_level, sizeof(m_current_mode), sizeof(m_current_mipmap_level));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create constant buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the vertex buffer array
  try
  {
    m_vert_array = VertexBufferArray::CreateD3D12(2);
    m_vert_array->Set(1, *m_instance);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

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

  CreateDepthStencil(graphics);
}

TestGraphicsPipeline::~TestGraphicsPipeline()
{
  delete m_depth_stencil;
  delete m_shader_buffer_heap;
  delete m_heap_array;
  delete m_constant_buffer_vs;
  delete m_constant_buffer_ps;
  delete m_instance;
  delete m_vert_array;
  delete m_command_list;
  delete m_pipeline;
  delete m_root_sig;
}

ShaderResourceDescHeap* TestGraphicsPipeline::GetShaderResourceDescHeap() const
{
  return m_shader_buffer_heap;
}

CommandList* TestGraphicsPipeline::GetCommandList() const
{
  return m_command_list;
}

void TestGraphicsPipeline::SetModel(const TestModel* model)
{
  m_model = model;

  // add the vertex buffer to the vertex buffer array
  try
  {
    m_vert_array->Set(0, *m_model->GetVertexBuffer());
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to set model vertex buffer into the vertex buffer array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void TestGraphicsPipeline::SetCamera(const Camera* cam)
{
  m_camera = cam;
}

void TestGraphicsPipeline::Draw(GraphicsCore& graphics)
{
  try
  {
    const IndexBuffer16* index_buffer = m_model->GetIndexBuffer();

    const RenderTarget& current_render_target = graphics.GetBackBuffer().GetCurrentRenderTarget();
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
    m_command_list->SetTextureAsStartOfDescriptorTable(0, *m_model->GetTexture()); // note: only binding the first texture in its descriptor heap to the slot since the others need to be contiguous after it
    m_command_list->SetConstantBuffer(1, *m_constant_buffer_vs);
    m_command_list->SetConstantBuffer(2, *m_constant_buffer_ps);

    float clear_color[4] = { .3f, .3f, .3f, 1 };
    m_command_list->PrepRenderTarget(current_render_target);
    m_command_list->OMSetRenderTarget(current_render_target, *m_depth_stencil);
    m_command_list->ClearRenderTarget(current_render_target, clear_color);
    m_command_list->ClearDepthStencil(*m_depth_stencil, 1);

    m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
    m_command_list->IASetVertexBuffers(*m_vert_array);
    m_command_list->IASetIndexBuffer(*index_buffer);

    m_command_list->DrawIndexedInstanced(index_buffer->GetNumIndices(), 2, 0);

    m_command_list->RenderTargetToPresent(current_render_target);
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

void TestGraphicsPipeline::Resize(GraphicsCore& graphics)
{
  const Viewport& full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(full_viewport);

  delete m_depth_stencil;
  CreateDepthStencil(graphics);
}

TextureModes TestGraphicsPipeline::GetMode() const
{
  return (TextureModes)m_current_mode;
}

void TestGraphicsPipeline::SetMode(TextureModes mode)
{
  m_current_mode = mode;
  m_constant_buffer_ps->Upload(&m_current_mode, 0, sizeof(m_current_mode));
}

UINT TestGraphicsPipeline::GetMipmapLevel() const
{
  return (TextureModes)m_current_mipmap_level;
}

void TestGraphicsPipeline::SetMipmapLevel(UINT level)
{
  m_current_mipmap_level = level;
  m_constant_buffer_ps->Upload(&m_current_mipmap_level, sizeof(m_current_mode), sizeof(m_current_mipmap_level));
}

void TestGraphicsPipeline::CreateDepthStencil(GraphicsCore& graphics)
{
  Viewport full_viewport = graphics.GetDefaultViewport();

  try
  {
    m_depth_stencil = DepthStencil::CreateD3D12(graphics, (UINT)full_viewport.width, (UINT)full_viewport.height, 1);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create depth stencil:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}
