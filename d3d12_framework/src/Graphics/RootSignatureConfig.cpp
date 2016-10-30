#include "Graphics/RootSignatureConfig.h"
#include "private_inc/D3D12/D3D12_RootSignatureConfig.h"

RootSignatureConfig* RootSignatureConfig::CreateD3D12(UINT num_params, UINT num_sampler)
{
  return new D3D12_RootSignatureConfig(num_params, num_sampler);
}

RootSignatureConfig::RootSignatureConfig()
{
}

RootSignatureConfig::~RootSignatureConfig()
{
}
