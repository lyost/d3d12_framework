#include "Graphics/Textures/Texture1D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture1D.h"

UINT Texture1D::GetAlignedSize(const GraphicsCore& graphics, UINT width, GraphicsDataFormat format)
{
  return D3D12_Texture1D::GetAlignedSize(graphics, width, format);
}

Texture1D* Texture1D::CreateD3D12(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, GraphicsDataFormat format)
{
  return D3D12_Texture1D::Create(graphics, resource_heap, shader_buffer_heap, width, format);
}

Texture1D::Texture1D()
{
}

Texture1D::~Texture1D()
{
}

Texture::TextureType Texture1D::GetType() const
{
  return TEXTURE_1D;
}
