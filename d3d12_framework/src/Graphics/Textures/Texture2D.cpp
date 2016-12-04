#include "Graphics/Textures/Texture2D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2D.h"

UINT Texture2D::GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height, GraphicsDataFormat format)
{
  return D3D12_Texture2D::GetAlignedSize(graphics, width, height, format);
}

Texture2D* Texture2D::CreateD3D12(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height,
  GraphicsDataFormat format)
{
  return D3D12_Texture2D::Create(graphics, resource_heap, shader_buffer_heap, width, height, format);
}

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
}