#include "Graphics/Textures/RenderTarget.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTarget.h"

RenderTarget* RenderTarget::CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, GraphicsDataFormat format)
{
  return D3D12_RenderTarget::Create(graphics, width, height, format);
}

RenderTarget::RenderTarget()
{
}

RenderTarget::~RenderTarget()
{
}
