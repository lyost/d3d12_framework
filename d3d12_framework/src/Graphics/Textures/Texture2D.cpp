#include "Graphics/Textures/Texture2D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2D.h"

Texture2D* Texture2D::CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format, UINT16 mip_levels)
{
  return D3D12_Texture2D::Create(graphics, shader_buffer_heap, width, height, format, mip_levels);
}

Texture2D::Texture2D()
{
}

Texture2D::~Texture2D()
{
}
