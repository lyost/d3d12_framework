#include "Graphics/Textures/TextureCubeArray.h"
#include "private_inc/D3D12/Textures/D3D12_TextureCubeArray.h"

TextureCubeArray* TextureCubeArray::CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 num_cubes, GraphicsDataFormat format,
  UINT16 mip_levels)
{
  return D3D12_TextureCubeArray::Create(graphics, shader_buffer_heap, width, height, num_cubes, format, mip_levels);
}

TextureCubeArray::TextureCubeArray()
{
}

TextureCubeArray::~TextureCubeArray()
{
}
