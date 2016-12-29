#include "Graphics/Textures/DepthStencil.h"
#include "private_inc/D3D12/Textures/D3D12_DepthStencil.h"

DepthStencil* DepthStencil::CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, float default_depth_clear)
{
  return D3D12_DepthStencil::Create(graphics, width, height, default_depth_clear);
}

DepthStencil::DepthStencil()
{
}

DepthStencil::~DepthStencil()
{
}