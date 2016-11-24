#include "Graphics/Pipeline.h"
#include "private_inc/D3D12/D3D12_Pipeline.h"

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& pixel_shader,
  const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, pixel_shader, rtv_config, root_sig, wireframe);
}

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& pixel_shader, DepthFuncs depth_func,
  const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, pixel_shader, depth_func, rtv_config, root_sig, wireframe);
}

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
  const Shader& domain_shader, const Shader& pixel_shader, DepthFuncs depth_func, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, hull_shader, domain_shader, pixel_shader, depth_func, rtv_config, root_sig, wireframe);
}

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& geometry_shader,
  const Shader& pixel_shader, DepthFuncs depth_func, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, geometry_shader, pixel_shader, depth_func, rtv_config, root_sig, wireframe);
}

Pipeline* Pipeline::CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& hull_shader,
  const Shader& domain_shader, const Shader& geometry_shader, const Shader& pixel_shader, DepthFuncs depth_func, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig, bool wireframe)
{
  return D3D12_Pipeline::Create(graphics_core, input_layout, topology, vertex_shader, hull_shader, domain_shader, geometry_shader, pixel_shader, depth_func, rtv_config, root_sig, wireframe);
}

Pipeline::Pipeline()
{
}

Pipeline::~Pipeline()
{
}
