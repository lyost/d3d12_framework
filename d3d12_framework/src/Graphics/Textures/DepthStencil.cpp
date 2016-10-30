#include "Graphics/Textures/DepthStencil.h"
#include "private_inc/D3D12/Textures/D3D12_DepthStencil.h"

UINT DepthStencil::GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height)
{
  return D3D12_DepthStencil::GetAlignedSize(graphics, width, height);
}

DepthStencil* DepthStencil::CreateD3D12(const GraphicsCore& graphics, DepthStencilResourceHeap& resource_heap, DepthStencilDescHeap& depth_stencil_buffer_heap, UINT width, UINT height,
  float default_depth_clear)
{
  return D3D12_DepthStencil::Create(graphics, resource_heap, depth_stencil_buffer_heap, width, height, default_depth_clear);
}

DepthStencil::DepthStencil()
{
}

DepthStencil::~DepthStencil()
{
}