#include <sstream>
#include "private_inc/D3D12/Textures/D3D12_DepthStencilResourceHeap.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "FrameworkException.h"
using namespace std;

D3D12_DepthStencilResourceHeap* D3D12_DepthStencilResourceHeap::Create(ID3D12Device* device, UINT64 num_bytes)
{
  D3D12_HEAP_DESC desc;
  desc.SizeInBytes                     = num_bytes;
  desc.Properties.Type                 = D3D12_HEAP_TYPE_DEFAULT;
  desc.Properties.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  desc.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  desc.Properties.CreationNodeMask     = 0;
  desc.Properties.VisibleNodeMask      = 0;
  desc.Alignment                       = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  desc.Flags                           = D3D12_HEAP_FLAG_ALLOW_ONLY_RT_DS_TEXTURES;

  ID3D12Heap* heap = NULL;
  HRESULT rc = device->CreateHeap(&desc, __uuidof(ID3D12Heap), (void**)&heap);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create depth stencil resource heap.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }

  return new D3D12_DepthStencilResourceHeap(num_bytes, heap);
}

D3D12_DepthStencilResourceHeap::D3D12_DepthStencilResourceHeap(UINT64 num_bytes, ID3D12Heap* heap)
:m_heap_total_size(num_bytes),
 m_heap_used_size(0),
 m_heap(heap)
{
}

ID3D12Resource* D3D12_DepthStencilResourceHeap::CreateResource(ID3D12Device* device, const D3D12_RESOURCE_DESC& resource_desc, float default_depth_clear)
{
  D3D12_CLEAR_VALUE clear;
  clear.Format               = DXGI_FORMAT_D32_FLOAT;
  clear.DepthStencil.Depth   = default_depth_clear;
  clear.DepthStencil.Stencil = 0;

  ID3D12Resource* buffer;
  HRESULT rc = device->CreatePlacedResource(m_heap, m_heap_used_size, &resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ, &clear, __uuidof(ID3D12Resource), (void**)&buffer);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create placed texture.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }

  D3D12_RESOURCE_ALLOCATION_INFO mem_info = device->GetResourceAllocationInfo(0, 1, &resource_desc);
  m_heap_used_size += mem_info.SizeInBytes;

  return buffer;
}

D3D12_DepthStencilResourceHeap::~D3D12_DepthStencilResourceHeap()
{
  m_heap->Release();
}

UINT64 D3D12_DepthStencilResourceHeap::GetHeapTotalSize() const
{
  return m_heap_total_size;
}

UINT64 D3D12_DepthStencilResourceHeap::GetHeapUsedSize() const
{
  return m_heap_used_size;
}
