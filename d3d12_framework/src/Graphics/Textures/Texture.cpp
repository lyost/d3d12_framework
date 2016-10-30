#include "Graphics/Textures/Texture.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2D.h"

UINT Texture::GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height, GraphicsDataFormat format)
{
  return D3D12_Texture2D::GetAlignedSize(graphics, width, height, format);
}

Texture* Texture::CreateD3D12_2D(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height,
  GraphicsDataFormat format)
{
  return D3D12_Texture2D::Create(graphics, resource_heap, shader_buffer_heap, width, height, format);
}

Texture::Texture()
{
}

Texture::~Texture()
{
}