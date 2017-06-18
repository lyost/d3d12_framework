#include "Graphics/Textures/DepthStencilMSAA.h"
#include "private_inc/D3D12/Textures/D3D12_DepthStencilMSAA.h"

DepthStencilMSAA* DepthStencilMSAA::CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, float default_depth_clear, bool with_stencil)
{
  return D3D12_DepthStencilMSAA::Create(graphics, width, height, sample_count, quality, default_depth_clear, with_stencil);
}

DepthStencilMSAA::DepthStencilMSAA()
{
}

DepthStencilMSAA::~DepthStencilMSAA()
{
}