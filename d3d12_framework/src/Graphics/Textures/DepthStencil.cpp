#include "Graphics/Textures/DepthStencil.h"
#include "private_inc/D3D12/Textures/D3D12_DepthStencil.h"

DepthStencil* DepthStencil::CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, float default_depth_clear, bool with_stencil)
{
  return D3D12_DepthStencil::Create(graphics, width, height, default_depth_clear, with_stencil);
}

DepthStencil::DepthStencil()
{
}

DepthStencil::~DepthStencil()
{
}