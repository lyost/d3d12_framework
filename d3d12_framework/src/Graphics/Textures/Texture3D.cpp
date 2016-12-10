#include "Graphics/Textures/Texture3D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture3D.h"

UINT Texture3D::GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height, UINT16 depth, GraphicsDataFormat format)
{
  return D3D12_Texture3D::GetAlignedSize(graphics, width, height, depth, format);
}

Texture3D* Texture3D::CreateD3D12(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 depth,
  GraphicsDataFormat format)
{
  return D3D12_Texture3D::Create(graphics, resource_heap, shader_buffer_heap, width, height, depth, format);
}

Texture3D::Texture3D()
{
}

Texture3D::~Texture3D()
{
}
