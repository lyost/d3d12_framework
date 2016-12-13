#include "Graphics/Textures/TextureUploadBuffer.h"
#include "private_inc/D3D12/Textures/D3D12_TextureUploadBuffer.h"

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture1D& texture, BufferResourceHeap& resource_heap)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture, resource_heap);
}

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture2D& texture, BufferResourceHeap& resource_heap)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture, resource_heap);
}

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture3D& texture, BufferResourceHeap& resource_heap)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture, resource_heap);
}

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture1DArray& texture, BufferResourceHeap& resource_heap)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture, resource_heap);
}

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture2DArray& texture, BufferResourceHeap& resource_heap)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture, resource_heap);
}

TextureUploadBuffer::TextureUploadBuffer()
{
}

TextureUploadBuffer::~TextureUploadBuffer()
{
}