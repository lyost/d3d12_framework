#include "Graphics/Textures/DepthStencilResourceHeap.h"
#include "private_inc/D3D12/Textures/D3D12_DepthStencilResourceHeap.h"

DepthStencilResourceHeap* DepthStencilResourceHeap::CreateD3D12(const GraphicsCore& core, UINT64 num_bytes)
{
  return D3D12_DepthStencilResourceHeap::Create(core, num_bytes);
}

DepthStencilResourceHeap::DepthStencilResourceHeap()
{
}

DepthStencilResourceHeap::~DepthStencilResourceHeap()
{
}
