#include "Graphics/Textures/TextureUploadBuffer.h"
#include "private_inc/D3D12/Textures/D3D12_TextureUploadBuffer.h"

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture1D& texture)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture);
}

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture2D& texture)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture);
}

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture3D& texture)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture);
}

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture1DArray& texture)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture);
}

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const Texture2DArray& texture)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture);
}

TextureUploadBuffer* TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const TextureCube& texture)
{
  return D3D12_TextureUploadBuffer::Create(graphics, texture);
}

TextureUploadBuffer::TextureUploadBuffer()
{
}

TextureUploadBuffer::~TextureUploadBuffer()
{
}
