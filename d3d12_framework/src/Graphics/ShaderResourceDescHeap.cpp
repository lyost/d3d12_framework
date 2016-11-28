#include "Graphics/ShaderResourceDescHeap.h"
#include "private_inc/D3D12/D3D12_ShaderResourceDescHeap.h"

ShaderResourceDescHeap* ShaderResourceDescHeap::CreateD3D12(const GraphicsCore& core, UINT num_descriptors)
{
  return D3D12_ShaderResourceDescHeap::Create(core, num_descriptors);
}

ShaderResourceDescHeap::ShaderResourceDescHeap()
{
}

ShaderResourceDescHeap::~ShaderResourceDescHeap()
{
}