#include "Graphics/Textures/Texture1D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture1D.h"

Texture1D* Texture1D::CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, GraphicsDataFormat format)
{
  return D3D12_Texture1D::Create(graphics, shader_buffer_heap, width, format);
}

Texture1D::Texture1D()
{
}

Texture1D::~Texture1D()
{
}
