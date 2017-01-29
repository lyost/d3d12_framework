#include "private_inc/D3D12/Textures/D3D12_TextureCubeArray.h"
#include "private_inc/D3D12/Textures/D3D12_Texture.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

TextureCubeArray* D3D12_TextureCubeArray::Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 num_cubes, GraphicsDataFormat format,
  UINT16 mip_levels)
{
  UINT32 num_sides = 6 * (UINT32)num_cubes;

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (num_sides != (UINT16)num_sides)
  {
    throw FrameworkException("Overflow detected when converting the number of cubes in a cube texture array to the number of sides");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_Texture::CreatedTexture tex = D3D12_Texture::Create(graphics, shader_buffer_heap, width, height, (UINT16)num_sides, format, D3D12_SRV_DIMENSION_TEXTURECUBEARRAY, D3D12_RESOURCE_FLAG_NONE,
    mip_levels);
  return new D3D12_TextureCubeArray(tex.buffer, tex.gpu_handle, width, height, (UINT16)num_sides, format, mip_levels);
}

D3D12_TextureCubeArray::D3D12_TextureCubeArray(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, UINT16 num_sides, GraphicsDataFormat format, UINT16 num_mip_levels)
:m_buffer(buffer),
 m_gpu_mem(gpu_mem),
 m_width(width),
 m_height(height),
 m_length(num_sides),
 m_format(format),
 m_num_mipmap_levels(num_mip_levels)
{
}

D3D12_TextureCubeArray::~D3D12_TextureCubeArray()
{
  m_buffer->Release();
}

ID3D12Resource* D3D12_TextureCubeArray::GetResource() const
{
  return m_buffer;
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12_TextureCubeArray::GetGPUAddr() const
{
  return m_gpu_mem;
}

UINT16 D3D12_TextureCubeArray::GetNumMipmapLevels() const
{
  return m_num_mipmap_levels;
}
