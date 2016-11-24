#include "private_inc/D3D12/Textures/D3D12_TextureResourceHeap.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

D3D12_TextureResourceHeap* D3D12_TextureResourceHeap::Create(const GraphicsCore& graphics, UINT64 num_bytes)
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  D3D12_HEAP_DESC desc;
  desc.SizeInBytes                     = num_bytes;
  desc.Properties.Type                 = D3D12_HEAP_TYPE_DEFAULT;
  desc.Properties.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  desc.Properties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  desc.Properties.CreationNodeMask     = 0;
  desc.Properties.VisibleNodeMask      = 0;
  desc.Alignment                       = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT; // todo: allow D3D12_DEFAULT_MSAA_RESOURCE_PLACEMENT_ALIGNMENT to be used when requested
  desc.Flags                           = D3D12_HEAP_FLAG_ALLOW_ONLY_NON_RT_DS_TEXTURES;

  ID3D12Heap* heap = NULL;
  HRESULT rc = device->CreateHeap(&desc, __uuidof(ID3D12Heap), (void**)&heap);
  if (FAILED(rc))
  {
    throw new FrameworkException("Failed to create texture upload heap");
  }

  return new D3D12_TextureResourceHeap(num_bytes, heap);
}

D3D12_TextureResourceHeap::D3D12_TextureResourceHeap(UINT64 num_bytes, ID3D12Heap* heap)
:m_heap_total_size(num_bytes),
 m_heap_used_size(0),
 m_heap(heap)
{
}

ID3D12Resource* D3D12_TextureResourceHeap::CreateResource(const GraphicsCore& graphics, const D3D12_RESOURCE_DESC& resource_desc)
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  ID3D12Resource* buffer;
  HRESULT rc = device->CreatePlacedResource(m_heap, m_heap_used_size, &resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, __uuidof(ID3D12Resource), (void**)&buffer);
  if (FAILED(rc))
  {
    throw new FrameworkException("Failed to create placed texture");
  }

  D3D12_RESOURCE_ALLOCATION_INFO mem_info = device->GetResourceAllocationInfo(0, 1, &resource_desc);
  m_heap_used_size += mem_info.SizeInBytes;

  return buffer;
}

D3D12_TextureResourceHeap::~D3D12_TextureResourceHeap()
{
  m_heap->Release();
}

UINT64 D3D12_TextureResourceHeap::GetHeapTotalSize() const
{
  return m_heap_total_size;
}

UINT64 D3D12_TextureResourceHeap::GetHeapUsedSize() const
{
  return m_heap_used_size;
}
