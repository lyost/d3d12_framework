#include "Graphics/Pipeline.h"
#include "private_inc/D3D12/D3D12_Pipeline.h"

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const StreamOutputConfig* stream_output,
  const Shader& pixel_shader, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, UINT ms_count, UINT ms_quality, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, stream_output, pixel_shader, rtv_config, root_sig, ms_count, ms_quality, wireframe);
}

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const StreamOutputConfig* stream_output,
  const Shader& pixel_shader, DepthFuncs depth_func, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, UINT ms_count, UINT ms_quality, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, stream_output, pixel_shader, depth_func, rtv_config, root_sig, ms_count, ms_quality, wireframe);
}

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
  const Shader& domain_shader, const StreamOutputConfig* stream_output, const Shader& pixel_shader, DepthFuncs depth_func, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig,
  UINT ms_count, UINT ms_quality, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, hull_shader, domain_shader, stream_output, pixel_shader, depth_func, rtv_config, root_sig, ms_count, ms_quality, wireframe);
}

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& geometry_shader,
  const StreamOutputConfig* stream_output, const Shader& pixel_shader, DepthFuncs depth_func, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, UINT ms_count, UINT ms_quality, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, geometry_shader, stream_output, pixel_shader, depth_func, rtv_config, root_sig, ms_count, ms_quality, wireframe);
}

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
  const Shader& domain_shader, const Shader& geometry_shader, const StreamOutputConfig* stream_output, const Shader& pixel_shader, DepthFuncs depth_func, const RenderTargetViewConfig& rtv_config,
  const RootSignature& root_sig, UINT ms_count, UINT ms_quality, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, hull_shader, domain_shader, geometry_shader, stream_output, pixel_shader, depth_func, rtv_config, root_sig, ms_count,
    ms_quality, wireframe);
}

Pipeline::Pipeline()
{
}

Pipeline::~Pipeline()
{
}
