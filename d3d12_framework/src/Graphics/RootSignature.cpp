#include "Graphics/RootSignature.h"
#include "private_inc/D3D12/D3D12_RootSignature.h"

RootSignature* RootSignature::CreateD3D12(const GraphicsCore& graphics, const RootSignatureConfig& config)
{
  return D3D12_RootSignature::Create(graphics, config);
}

RootSignature::RootSignature()
{
}

RootSignature::~RootSignature()
{
}
