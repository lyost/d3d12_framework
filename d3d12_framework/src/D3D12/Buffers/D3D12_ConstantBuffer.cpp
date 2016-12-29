#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_ConstantBuffer.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_ShaderResourceDescHeap.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

D3D12_ConstantBuffer* D3D12_ConstantBuffer::Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT num_bytes)
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  D3D12_ShaderResourceDescHeap& desc_heap = (D3D12_ShaderResourceDescHeap&)shader_buffer_heap;
  D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle;
  desc_heap.GetNextDescriptor(cpu_handle, gpu_handle);

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(num_bytes, resource_desc);
  D3D12_HEAP_PROPERTIES heap_prop;
  heap_prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
  heap_prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  heap_prop.CreationNodeMask     = 0;
  heap_prop.VisibleNodeMask      = 0;

  ID3D12Resource* buffer;
  HRESULT rc = device->CreateCommittedResource(&heap_prop, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, __uuidof(ID3D12Resource), (void**)&buffer);
  if (FAILED(rc))
  {
    throw FrameworkException("Unable to create buffer resource");
  }

  D3D12_CONSTANT_BUFFER_VIEW_DESC view_desc;
  view_desc.BufferLocation = buffer->GetGPUVirtualAddress();
  view_desc.SizeInBytes    = num_bytes;
  device->CreateConstantBufferView(&view_desc, cpu_handle);
  
  UINT8* host_mem;
  D3D12_RANGE range;
  range.Begin = 0;
  range.End   = 0;
  rc = buffer->Map(0, &range, (void**)&host_mem);
  if (FAILED(rc))
  {
    buffer->Release();

    ostringstream out;
    out << "Failed to map constant buffer memory.  HRESULT = " << rc;
    throw FrameworkException(out.str());
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
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  UINT total = start + len;
  if (total > m_num_bytes)
  {
    throw FrameworkException("attempting to send more bytes than are available in the buffer");
  }
  if (total < start)
  {
    throw FrameworkException("rollover detected");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  memcpy(m_host_mem_start + start, data, len);
}

D3D12_GPU_VIRTUAL_ADDRESS D3D12_ConstantBuffer::GetGPUAddr() const
{
  return m_gpu_mem;
}

void D3D12_ConstantBuffer::GetResourceDesc(UINT& num_bytes, D3D12_RESOURCE_DESC& resource_desc)
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