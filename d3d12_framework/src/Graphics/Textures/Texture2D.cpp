#include "Graphics/Textures/Texture2D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2D.h"

Texture2D* Texture2D::CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format)
{
  return D3D12_Texture2D::Create(graphics, shader_buffer_heap, width, height, format);
}

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
}

Texture::TextureType Texture2D::GetType() const
{
  return TEXTURE_2D;
}
