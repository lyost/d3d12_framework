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
    RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(3, 1);
    config->SetStageAccess(true, true, false, false, false, true, false);
    config->SetParamAsDescriptorTable(0, 1, SHADER_VISIBILITY_PIXEL);
    config->SetRangeAsShaderResourceView(0, 0, 1, 0, 0);
    config->SetParamAsConstantBufferView(1, 0, 0, SHADER_VISIBILITY_VERTEX);
    config->SetParamAsConstantBufferView(2, 0, 0, SHADER_VISIBILITY_PIXEL);
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

  Shader* vertex_shader;
  Shader* pixel_shader_shadow;
  Shader* pixel_shader;
  InputLayout* input_layout;
  try
  {
    vertex_shader = Shader::LoadD3D12("stencil_vs.cso");
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
    pixel_shader_shadow = Shader::LoadD3D12("stencil_ps_shadow.cso");
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
    pixel_shader = Shader::LoadD3D12("stencil_ps.cso");
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
    input_layout->SetNextElement(SEM_TEXCOORD, 0, R32G32_FLOAT,    0, false);
    input_layout->SetNextElement(SEM_NORMAL,   0, R32G32B32_FLOAT, 0, false);
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
    ds_config.dsv_format          = D32_FLOAT_S8_UINT;
    ds_config.depth_write_enabled = true;
    ds_config.depth_comparison    = COMPARISON_FUNC_LESS_EQUAL;
    RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
    rtv_config->SetAlphaToCoverageEnable(false);
    rtv_config->SetIndependentBlendEnable(false);
    rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
    m_pipeline_shadow = Pipeline::CreateD3D12(graphics, *input_layout, TOPOLOGY_TRIANGLE, *vertex_shader, NULL, *pixel_shader_shadow, &ds_config, *rtv_config, *m_root_sig);
    
    ds_config.stencil_enable      = true;
    ds_config.depth_write_enabled = false;
    ds_config.stencil_read_mask   = 0xff;
    ds_config.stencil_write_mask  = 0xff;
    ds_config.stencil_front_face.stencil_fail = SOP_KEEP;
    ds_config.stencil_front_face.depth_fail   = SOP_DECREMENT_ROLLOVER;
    ds_config.stencil_front_face.pass         = SOP_KEEP;
    ds_config.stencil_front_face.comparison   = COMPARISON_FUNC_ALWAYS;
    ds_config.stencil_back_face.stencil_fail  = SOP_KEEP;
    ds_config.stencil_back_face.depth_fail    = SOP_INCREMENT_ROLLOVER;
    ds_config.stencil_back_face.pass          = SOP_KEEP;
    ds_config.stencil_back_face.comparison    = COMPARISON_FUNC_ALWAYS;
    rtv_config->DisableColorWrite(0);
    m_pipeline_depth_fail = Pipeline::CreateD3D12(graphics, *input_layout, TOPOLOGY_TRIANGLE, *vertex_shader, NULL, *pixel_shader_shadow, &ds_config, *rtv_config, *m_root_sig, CULL_NONE);

    ds_config.depth_write_enabled = true;
    ds_config.stencil_front_face.stencil_fail = SOP_REPLACE;
    ds_config.stencil_front_face.depth_fail   = SOP_REPLACE;
    ds_config.stencil_front_face.pass         = SOP_REPLACE;
    ds_config.stencil_front_face.comparison   = COMPARISON_FUNC_EQUAL;
    ds_config.stencil_back_face.stencil_fail  = SOP_REPLACE;
    ds_config.stencil_back_face.depth_fail    = SOP_REPLACE;
    ds_config.stencil_back_face.pass          = SOP_REPLACE;
    ds_config.stencil_back_face.comparison    = COMPARISON_FUNC_EQUAL;
    rtv_config->EnableColorWrite(0);
    m_pipeline_lit = Pipeline::CreateD3D12(graphics, *input_layout, TOPOLOGY_TRIANGLE, *vertex_shader, NULL, *pixel_shader, &ds_config, *rtv_config, *m_root_sig);

    delete rtv_config;
    delete input_layout;
    delete pixel_shader_shadow;
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
    m_command_list = CommandList::CreateD3D12Direct(graphics, m_pipeline_lit);
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

  // create vertex buffer array
  try
  {
    m_vert_array = VertexBufferArray::CreateD3D12(1);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer array:\n" << err.what();
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

  // create the constant buffer
  try
  {
    m_constant_buffer_occluder = ConstantBuffer::CreateD3D12(graphics, *m_shader_buffer_heap, sizeof(XMMATRIX) * 3);
    m_constant_buffer_model    = ConstantBuffer::CreateD3D12(graphics, *m_shader_buffer_heap, sizeof(XMMATRIX) * 3);
    m_constant_buffer_lighting = ConstantBuffer::CreateD3D12(graphics, *m_shader_buffer_heap, sizeof(XMFLOAT3) * 2);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create constant buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  CreateDepthStencil(graphics);

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
}

TestGraphicsPipeline::~TestGraphicsPipeline()
{
  delete m_depth_stencil;
  delete m_shader_buffer_heap;
  delete m_heap_array;
  delete m_constant_buffer_lighting;
  delete m_constant_buffer_occluder;
  delete m_constant_buffer_model;
  delete m_vert_array;
  delete m_command_list;
  delete m_pipeline_shadow;
  delete m_pipeline_depth_fail;
  delete m_pipeline_lit;
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

void TestGraphicsPipeline::SetLightPos(const XMFLOAT3& light_pos)
{
  m_light_pos = light_pos;
  m_constant_buffer_lighting->Upload(&m_light_pos, 0, sizeof(m_light_pos));
}

void TestGraphicsPipeline::SetOccluder(const Occluder* model)
{
  m_occluder = model;
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
  XMFLOAT4 cam_pos = cam->GetPosition();
  m_constant_buffer_lighting->Upload(&cam_pos, sizeof(XMFLOAT3), sizeof(XMFLOAT3));
}

void TestGraphicsPipeline::Draw(GraphicsCore& graphics)
{
  try
  {
    const RenderTarget& current_render_target = graphics.GetBackBuffer().GetCurrentRenderTarget();
    DrawShadowPass(graphics, current_render_target);
    DrawDepthFailPass(graphics, current_render_target);
    DrawLitPass(graphics, current_render_target);

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

void TestGraphicsPipeline::CreateDepthStencil(GraphicsCore& graphics)
{
  Viewport full_viewport = graphics.GetDefaultViewport();

  try
  {
    m_depth_stencil = DepthStencil::CreateD3D12(graphics, (UINT)full_viewport.width, (UINT)full_viewport.height, 1, true);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create depth stencil:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

void TestGraphicsPipeline::DrawShadowPass(GraphicsCore& graphics, const RenderTarget& render_target)
{
  m_command_list->Reset(m_pipeline_shadow);
  m_command_list->SetRootSignature(*m_root_sig);
  m_command_list->RSSetViewport(graphics.GetDefaultViewport());
  m_command_list->RSSetScissorRect(m_scissor_rect);

  m_command_list->SetConstantBuffer(2, *m_constant_buffer_lighting);

  XMFLOAT3 pos = m_model->GetWorldPos();
  XMMATRIX tmp = XMMatrixTranslation(pos.x, pos.y, pos.z);
  m_constant_buffer_model->Upload(&tmp, 0, sizeof(tmp));
  tmp = XMMatrixIdentity();
  m_constant_buffer_occluder->Upload(&tmp, 0, sizeof(tmp));

  m_camera->GetView(tmp);
  m_constant_buffer_model->Upload(&tmp, sizeof(tmp), sizeof(tmp));
  m_constant_buffer_occluder->Upload(&tmp, sizeof(tmp), sizeof(tmp));

  m_camera->GetProjection(tmp);
  m_constant_buffer_model->Upload(&tmp, sizeof(tmp) * 2, sizeof(tmp));
  m_constant_buffer_occluder->Upload(&tmp, sizeof(tmp) * 2, sizeof(tmp));

  m_command_list->SetHeapArray(*m_heap_array);

  float clear_color[4] = { .3f, .3f, .3f, 1 };
  m_command_list->PrepRenderTarget(render_target);
  m_command_list->OMSetRenderTarget(render_target, *m_depth_stencil);
  m_command_list->ClearRenderTarget(render_target, clear_color);
  m_command_list->ClearDepthStencil(*m_depth_stencil, 1);

  // draw test model
  m_command_list->SetConstantBuffer(1, *m_constant_buffer_model);
  m_command_list->SetTextureAsStartOfDescriptorTable(0, *m_model->GetTexture());
  m_vert_array->Set(0, *m_model->GetVertexBuffer());
  const IndexBuffer16* index_buffer = m_model->GetIndexBuffer();
  m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
  m_command_list->IASetVertexBuffers(*m_vert_array);
  m_command_list->IASetIndexBuffer(*index_buffer);
  m_command_list->DrawIndexedInstanced(index_buffer->GetNumIndices(), 1, 0);

  // draw occluder
  m_command_list->SetConstantBuffer(1, *m_constant_buffer_occluder);
  m_command_list->SetTextureAsStartOfDescriptorTable(0, *m_occluder->GetTexture());
  m_vert_array->Set(0, *m_occluder->GetVertexBuffer());
  index_buffer = m_occluder->GetIndexBuffer();
  m_command_list->IASetVertexBuffers(*m_vert_array);
  m_command_list->IASetIndexBuffer(*index_buffer);
  m_command_list->DrawIndexedInstanced(index_buffer->GetNumIndices(), 1, 0);
}

void TestGraphicsPipeline::DrawDepthFailPass(GraphicsCore& graphics, const RenderTarget& render_target)
{
  m_command_list->SetPipeline(*m_pipeline_depth_fail);

  // draw shadow volume
  const ShadowVolume* shadow_volume = m_occluder->GetShadowVolume();
  m_command_list->SetConstantBuffer(1, *m_constant_buffer_occluder);
  m_command_list->SetTextureAsStartOfDescriptorTable(0, *m_occluder->GetTexture());
  m_vert_array->Set(0, *shadow_volume->GetVertexBuffer());
  const IndexBuffer16* index_buffer = shadow_volume->GetIndexBuffer();
  m_command_list->IASetVertexBuffers(*m_vert_array);
  m_command_list->IASetIndexBuffer(*index_buffer);
  m_command_list->DrawIndexedInstanced(index_buffer->GetNumIndices(), 1, 0);
}

void TestGraphicsPipeline::DrawLitPass(GraphicsCore& graphics, const RenderTarget& render_target)
{
  m_command_list->SetPipeline(*m_pipeline_lit);

  // draw test model
  m_command_list->SetConstantBuffer(1, *m_constant_buffer_model);
  m_command_list->SetTextureAsStartOfDescriptorTable(0, *m_model->GetTexture());
  m_vert_array->Set(0, *m_model->GetVertexBuffer());
  const IndexBuffer16* index_buffer = m_model->GetIndexBuffer();
  m_command_list->IASetVertexBuffers(*m_vert_array);
  m_command_list->IASetIndexBuffer(*index_buffer);
  m_command_list->DrawIndexedInstanced(index_buffer->GetNumIndices(), 1, 0);

  // draw occluder
  m_command_list->SetConstantBuffer(1, *m_constant_buffer_occluder);
  m_command_list->SetTextureAsStartOfDescriptorTable(0, *m_occluder->GetTexture());
  m_vert_array->Set(0, *m_occluder->GetVertexBuffer());
  index_buffer = m_occluder->GetIndexBuffer();
  m_command_list->IASetVertexBuffers(*m_vert_array);
  m_command_list->IASetIndexBuffer(*index_buffer);
  m_command_list->DrawIndexedInstanced(index_buffer->GetNumIndices(), 1, 0);
}
