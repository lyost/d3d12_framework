#include "Graphics/RenderTargetViewConfig.h"
#include "private_inc/D3D12/D3D12_RenderTargetViewConfig.h"

RenderTargetViewConfig* RenderTargetViewConfig::CreateD3D12(UINT num)
{
  return new D3D12_RenderTargetViewConfig(num);
}

RenderTargetViewConfig::RenderTargetViewConfig()
{
}

RenderTargetViewConfig::~RenderTargetViewConfig()
{
}
