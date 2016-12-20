#include "Graphics/Textures/TextureUploadBuffer.h"
#include "private_inc/D3D12/Textures/D3D12_TextureUploadBuffer.h"

void TextureUploadBuffer::CreateD3D12(const GraphicsCore& graphics, const std::vector<Texture*>& textures, std::vector<TextureUploadBuffer*>& out)
{
  D3D12_TextureUploadBuffer::Create(graphics, textures, out);
}

TextureUploadBuffer::TextureUploadBuffer()
{
}

TextureUploadBuffer::~TextureUploadBuffer()
{
}
