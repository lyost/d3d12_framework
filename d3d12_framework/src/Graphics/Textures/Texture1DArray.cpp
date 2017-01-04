#include "Graphics/Textures/Texture1DArray.h"
#include "private_inc/D3D12/Textures/D3D12_Texture1DArray.h"

Texture1DArray* Texture1DArray::CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT16 length, GraphicsDataFormat format, UINT16 mip_levels)
{
  return D3D12_Texture1DArray::Create(graphics, shader_buffer_heap, width, length, format, mip_levels);
}

Texture1DArray::Texture1DArray()
{
}

Texture1DArray::~Texture1DArray()
{
}
