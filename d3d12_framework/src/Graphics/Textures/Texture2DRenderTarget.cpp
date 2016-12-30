#include "Graphics/Textures/Texture2DRenderTarget.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2DRenderTarget.h"

Texture2DRenderTarget* Texture2DRenderTarget::CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format)
{
  return D3D12_Texture2DRenderTarget::Create(graphics, shader_buffer_heap, width, height, format);
}

Texture2DRenderTarget::Texture2DRenderTarget()
{
}

Texture2DRenderTarget::~Texture2DRenderTarget()
{
}
