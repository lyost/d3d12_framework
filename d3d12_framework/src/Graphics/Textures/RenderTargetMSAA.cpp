#include "Graphics/Textures/RenderTargetMSAA.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTargetMSAA.h"

RenderTargetMSAA* RenderTargetMSAA::CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, RenderTargetViewFormat format)
{
  return D3D12_RenderTargetMSAA::Create(graphics, width, height, sample_count, quality, format);
}

RenderTargetMSAA* RenderTargetMSAA::CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, RenderTargetViewFormat format, float clear_color[4])
{
  return D3D12_RenderTargetMSAA::Create(graphics, width, height, sample_count, quality, format, clear_color);
}

RenderTargetMSAA::RenderTargetMSAA()
{
}

RenderTargetMSAA::~RenderTargetMSAA()
{
}
