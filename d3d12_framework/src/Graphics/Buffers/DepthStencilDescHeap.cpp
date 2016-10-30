#include "Graphics/Buffers/DepthStencilDescHeap.h"
#include "private_inc/D3D12/Buffers/D3D12_DepthStencilDescHeap.h"

DepthStencilDescHeap* DepthStencilDescHeap::CreateD3D12(const GraphicsCore& core, UINT num_descriptors)
{
  return D3D12_DepthStencilDescHeap::Create(core, num_descriptors);
}

DepthStencilDescHeap::DepthStencilDescHeap()
{
}

DepthStencilDescHeap::~DepthStencilDescHeap()
{
}