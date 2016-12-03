#include "private_inc/D3D12/Textures/D3D12_RenderTargetResourceHeap.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

D3D12_RenderTargetResourceHeap* D3D12_RenderTargetResourceHeap::Create(ID3D12Device* device, UINT64 num_bytes)
{
  D3D12_HEAP_DESC desc;
  desc.SizeInBytes                     = num_bytes;
  desc.Properties.Type                 = D3D12_HEAP_TYPE_DEFAULT;
  desc.Properties.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  desc.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  desc.Properties.CreationNodeMask     = 0;
  desc.Properties.VisibleNodeMask      = 0;
  desc.Alignment                       = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT; // todo: allow D3D12_DEFAULT_MSAA_RESOURCE_PLACEMENT_ALIGNMENT to be used when requested
  desc.Flags                           = D3D12_HEAP_FLAG_ALLOW_ONLY_RT_DS_TEXTURES;

  ID3D12Heap* heap = NULL;
  HRESULT rc = device->CreateHeap(&desc, __uuidof(ID3D12Heap), (void**)&heap);
  if (FAILED(rc))
  {
    throw FrameworkException("Failed to create render target heap");
  }

  return new D3D12_RenderTargetResourceHeap(num_bytes, heap);
}

D3D12_RenderTargetResourceHeap::D3D12_RenderTargetResourceHeap(UINT64 num_bytes, ID3D12Heap* heap)
:m_heap_total_size(num_bytes),
 m_heap_used_size(0),
 m_heap(heap)
{
}

ID3D12Resource* D3D12_RenderTargetResourceHeap::CreateResource(ID3D12Device* device, const D3D12_RESOURCE_DESC& resource_desc)
{
  ID3D12Resource* buffer;
  D3D12_CLEAR_VALUE clear_value;
  clear_value.Format   = resource_desc.Format;
  clear_value.Color[0] = 0;
  clear_value.Color[1] = 0;
  clear_value.Color[2] = 0;
  clear_value.Color[3] = 1;
  HRESULT rc = device->CreatePlacedResource(m_heap, m_heap_used_size, &resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ, &clear_value, __uuidof(ID3D12Resource), (void**)&buffer);
  if (FAILED(rc))
  {
    throw FrameworkException("Failed to create placed render target");
  }

  D3D12_RESOURCE_ALLOCATION_INFO mem_info = device->GetResourceAllocationInfo(0, 1, &resource_desc);
  m_heap_used_size += mem_info.SizeInBytes;

  return buffer;
}

D3D12_RenderTargetResourceHeap::~D3D12_RenderTargetResourceHeap()
{
  m_heap->Release();
}

UINT64 D3D12_RenderTargetResourceHeap::GetHeapTotalSize() const
{
  return m_heap_total_size;
}

UINT64 D3D12_RenderTargetResourceHeap::GetHeapUsedSize() const
{
  return m_heap_used_size;
}
