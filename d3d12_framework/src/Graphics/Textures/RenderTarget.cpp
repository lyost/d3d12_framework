#include "Graphics/Textures/RenderTarget.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTarget.h"

RenderTarget* RenderTarget::CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, GraphicsDataFormat format)
{
  return D3D12_RenderTarget::Create(graphics, width, height, format);
}

RenderTarget* RenderTarget::CreateD3D12FromTexture(const GraphicsCore& graphics, const Texture2DRenderTarget& texture)
{
  return D3D12_RenderTarget::CreateFromTexture(graphics, texture);
}

RenderTarget::RenderTarget()
{
}

RenderTarget::~RenderTarget()
{
}
