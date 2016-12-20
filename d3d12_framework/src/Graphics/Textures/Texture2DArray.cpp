#include "Graphics/Textures/Texture2DArray.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2DArray.h"

UINT Texture2DArray::GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height, UINT16 length, GraphicsDataFormat format)
{
  return D3D12_Texture2DArray::GetAlignedSize(graphics, width, height, length, format);
}

Texture2DArray* Texture2DArray::CreateD3D12(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 length,
  GraphicsDataFormat format)
{
  return D3D12_Texture2DArray::Create(graphics, resource_heap, shader_buffer_heap, width, height, length, format);
}

Texture2DArray::Texture2DArray()
{
}

Texture2DArray::~Texture2DArray()
{
}

Texture::TextureType Texture2DArray::GetType() const
{
  return TEXTURE_2D_ARRAY;
}
