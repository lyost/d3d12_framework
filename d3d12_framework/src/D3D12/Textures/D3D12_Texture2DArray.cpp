#include "private_inc/D3D12/Textures/D3D12_Texture2DArray.h"
#include "private_inc/D3D12/Textures/D3D12_Texture.h"

Texture2DArray* D3D12_Texture2DArray::Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 length, GraphicsDataFormat format)
{
  D3D12_Texture::CreatedTexture tex = D3D12_Texture::Create(graphics, shader_buffer_heap, width, height, length, format, D3D12_SRV_DIMENSION_TEXTURE2DARRAY, D3D12_RESOURCE_FLAG_NONE);
  return new D3D12_Texture2DArray(tex.buffer, tex.gpu_handle, width, height, length, format);
}

D3D12_Texture2DArray::D3D12_Texture2DArray(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, UINT16 length, GraphicsDataFormat format)
:m_buffer(buffer),
 m_gpu_mem(gpu_mem),
 m_width(width),
 m_height(height),
 m_length(length),
 m_format(format)
{
}

D3D12_Texture2DArray::~D3D12_Texture2DArray()
{
  m_buffer->Release();
}

UINT16 D3D12_Texture2DArray::GetLength() const
{
  return m_length;
}

ID3D12Resource* D3D12_Texture2DArray::GetBuffer() const
{
  return m_buffer;
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12_Texture2DArray::GetGPUAddr() const
{
  return m_gpu_mem;
}
