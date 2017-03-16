#include <sstream>
#include <directxmath.h>
#include "TestGraphicsPipeline.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

TestGraphicsPipeline::TestGraphicsPipeline(GraphicsCore& graphics)
:m_model(NULL)
{
  try
  {
    RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(1, 1);
    config->SetStageAccess(true, true, false, false, false, true, false);
    config->SetParamAsDescriptorTable(0, 1, SHADER_VISIBILITY_PIXEL);
    config->SetRangeAsShaderResourceView(0, 0, 1, 0, 0);
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
    m_vertex_shader = Shader::LoadD3D12("single_2d_texture_vs.cso");
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
    m_pixel_shader = Shader::LoadD3D12("single_2d_texture_ps.cso");
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
    m_pipeline = Pipeline::CreateD3D12(graphics, *m_input_layout, TOPOLOGY_TRIANGLE, *m_vertex_shader, NULL, *m_pixel_shader, *rtv_config, *m_root_sig);
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

  // create the scissor rect that matches the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  try
  {
    m_shader_buffer_heap = ShaderResourceDescHeap::CreateD3D12(graphics, 1);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create resource descriptor heap:\n" << err.what();
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
}

TestGraphicsPipeline::~TestGraphicsPipeline()
{
  delete m_vert_array;
  delete m_heap_array;
  delete m_shader_buffer_heap;
  delete m_vertex_shader;
  delete m_pixel_shader;
  delete m_input_layout;
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

void TestGraphicsPipeline::Draw(GraphicsCore& graphics)
{
  try
  {
    const RenderTarget& current_render_target = graphics.GetBackBuffer().GetCurrentRenderTarget();
    m_command_list->Reset(m_pipeline);
    m_command_list->SetRootSignature(*m_root_sig);
    m_command_list->SetHeapArray(*m_heap_array);
    m_command_list->SetTextureAsStartOfDescriptorTable(0, *m_model->GetTexture());
    m_command_list->RSSetViewport(graphics.GetDefaultViewport());
    m_command_list->RSSetScissorRect(m_scissor_rect);

    float clear_color[4] = { .3f, .3f, .3f, 1 };
    m_command_list->PrepRenderTarget(current_render_target);
    m_command_list->OMSetRenderTarget(current_render_target);
    m_command_list->ClearRenderTarget(current_render_target, clear_color);

    m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
    m_command_list->IASetVertexBuffers(*m_vert_array);

    m_command_list->DrawInstanced(m_model->GetVertexBuffer()->GetNumVertices(), 1, 0);

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
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());
}
