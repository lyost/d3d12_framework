#include "private_inc/D3D12/Textures/D3D12_Texture1D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture.h"

Texture1D* D3D12_Texture1D::Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, GraphicsDataFormat format, UINT16 mip_levels)
{
  D3D12_Texture::CreatedTexture tex = D3D12_Texture::Create(graphics, shader_buffer_heap, width, 1, 1, format, D3D12_SRV_DIMENSION_TEXTURE1D, D3D12_RESOURCE_FLAG_NONE, mip_levels);
  return new D3D12_Texture1D(tex.buffer, tex.gpu_handle, width, format, mip_levels);
}

D3D12_Texture1D::D3D12_Texture1D(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, GraphicsDataFormat format, UINT16 num_mip_levels)
:m_buffer(buffer),
 m_gpu_mem(gpu_mem),
 m_width(width),
 m_format(format),
 m_num_mipmap_levels(num_mip_levels)
{
}

D3D12_Texture1D::~D3D12_Texture1D()
{
  m_buffer->Release();
}

ID3D12Resource* D3D12_Texture1D::GetResource() const
{
  return m_buffer;
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12_Texture1D::GetGPUAddr() const
{
  return m_gpu_mem;
}

UINT16 D3D12_Texture1D::GetNumMipmapLevels() const
{
  return m_num_mipmap_levels;
}
