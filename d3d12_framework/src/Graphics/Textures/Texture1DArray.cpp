#include "Graphics/Textures/Texture1DArray.h"
#include "private_inc/D3D12/Textures/D3D12_Texture1DArray.h"

UINT Texture1DArray::GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT16 length, GraphicsDataFormat format)
{
  return D3D12_Texture1DArray::GetAlignedSize(graphics, width, length, format);
}

Texture1DArray* Texture1DArray::CreateD3D12(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT16 length,
  GraphicsDataFormat format)
{
  return D3D12_Texture1DArray::Create(graphics, resource_heap, shader_buffer_heap, width, length, format);
}

Texture1DArray::Texture1DArray()
{
}

Texture1DArray::~Texture1DArray()
{
}

Texture::TextureType Texture1DArray::GetType() const
{
  return TEXTURE_1D_ARRAY;
}
