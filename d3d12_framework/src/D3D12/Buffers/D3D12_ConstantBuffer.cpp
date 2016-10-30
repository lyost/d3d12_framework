#include "private_inc/D3D12/Buffers/D3D12_ConstantBuffer.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/Buffers/D3D12_BufferResourceHeap.h"
#include "private_inc/D3D12/Buffers/D3D12_ShaderResourceDescHeap.h"
#include "log.h"

UINT D3D12_ConstantBuffer::GetAlignedSize(const GraphicsCore& graphics, UINT num_bytes)
{
  const D3D12_Core& core = (const D3D12_Core&)graphics;
  ID3D12Device* device = core.GetDevice();

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(num_bytes, resource_desc);

  D3D12_RESOURCE_ALLOCATION_INFO alloc_info = device->GetResourceAllocationInfo(0, 1, &resource_desc);
  if (alloc_info.SizeInBytes > (UINT)alloc_info.SizeInBytes)
  {
    return -1;
  }
  else
  {
    return (UINT)alloc_info.SizeInBytes;
  }
}

D3D12_ConstantBuffer* D3D12_ConstantBuffer::Create(const GraphicsCore& graphics, BufferResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT num_bytes)
{
  const D3D12_Core& core = (const D3D12_Core&)graphics;
  ID3D12Device* device = core.GetDevice();

  D3D12_ShaderResourceDescHeap& desc_heap = (D3D12_ShaderResourceDescHeap&)shader_buffer_heap;
  D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle;
  desc_heap.GetNextDescriptor(cpu_handle, gpu_handle);

  D3D12_BufferResourceHeap& buffer_heap = (D3D12_BufferResourceHeap&)resource_heap;

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(num_bytes, resource_desc);

  ID3D12Resource* buffer = buffer_heap.CreateResource(graphics, resource_desc);
  if (buffer == NULL)
  {
    return NULL;
  }

  D3D12_CONSTANT_BUFFER_VIEW_DESC view_desc;
  view_desc.BufferLocation = buffer->GetGPUVirtualAddress();
  view_desc.SizeInBytes    = num_bytes;
  device->CreateConstantBufferView(&view_desc, cpu_handle);
  
  UINT8* host_mem;
  D3D12_RANGE range;
  range.Begin = 0;
  range.End   = 0;
  HRESULT rc = buffer->Map(0, &range, (void**)&host_mem);
  if (FAILED(rc))
  {
    buffer->Release();
    log_print("Failed to map constant buffer memory");
    return NULL;
  }

  return new D3D12_ConstantBuffer(buffer, host_mem, view_desc.BufferLocation, num_bytes);
}

D3D12_ConstantBuffer::D3D12_ConstantBuffer(ID3D12Resource* buffer, UINT8* host_mem_start, D3D12_GPU_VIRTUAL_ADDRESS gpu_mem, UINT num_bytes)
:m_buffer(buffer),
 m_host_mem_start(host_mem_start),
 m_gpu_mem(gpu_mem),
 m_num_bytes(num_bytes)
{
}

D3D12_ConstantBuffer::~D3D12_ConstantBuffer()
{
  m_buffer->Unmap(0, NULL);
  m_buffer->Release();
}

void D3D12_ConstantBuffer::Upload(void* data, UINT start, UINT len)
{
  memcpy(m_host_mem_start + start, data, len);
}

D3D12_GPU_VIRTUAL_ADDRESS D3D12_ConstantBuffer::GetGPUAddr() const
{
  return m_gpu_mem;
}

void D3D12_ConstantBuffer::GetResourceDesc(UINT num_bytes, D3D12_RESOURCE_DESC& resource_desc)
{
  // constant buffer size is required to be 256-byte aligned
  num_bytes = (num_bytes + 255) & ~255;

  resource_desc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
  resource_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  resource_desc.Width              = num_bytes;
  resource_desc.Height             = 1;
  resource_desc.DepthOrArraySize   = 1;
  resource_desc.MipLevels          = 1;
  resource_desc.Format             = DXGI_FORMAT_UNKNOWN;
  resource_desc.SampleDesc.Count   = 1;
  resource_desc.SampleDesc.Quality = 0;
  resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  resource_desc.Flags              = D3D12_RESOURCE_FLAG_NONE;
}