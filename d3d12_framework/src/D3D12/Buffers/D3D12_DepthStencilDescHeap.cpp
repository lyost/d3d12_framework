#include "private_inc/D3D12/Buffers/D3D12_DepthStencilDescHeap.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "log.h"

// todo: add class for D3D12_ShaderSamplerHeap

D3D12_DepthStencilDescHeap* D3D12_DepthStencilDescHeap::Create(const GraphicsCore& graphics, UINT num_descriptors)
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  D3D12_DESCRIPTOR_HEAP_DESC desc;
  desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
  desc.NumDescriptors = num_descriptors;
  desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
  desc.NodeMask       = 0;

  ID3D12DescriptorHeap* heap = NULL;
  HRESULT rc = device->CreateDescriptorHeap(&desc, __uuidof(ID3D12DescriptorHeap), (void**)&heap);
  if (FAILED(rc))
  {
    log_print("Failed to create descriptor heap for depth stencils");
    return NULL;
  }

  UINT increment_size = device->GetDescriptorHandleIncrementSize(desc.Type);

  D3D12_CPU_DESCRIPTOR_HANDLE cpu_start = heap->GetCPUDescriptorHandleForHeapStart();
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_start = heap->GetGPUDescriptorHandleForHeapStart();

  return new D3D12_DepthStencilDescHeap(num_descriptors, cpu_start, gpu_start, increment_size, heap);
}

D3D12_DepthStencilDescHeap::D3D12_DepthStencilDescHeap(UINT num_descriptors, const D3D12_CPU_DESCRIPTOR_HANDLE& cpu_start, const D3D12_GPU_DESCRIPTOR_HANDLE& gpu_start, UINT descriptor_size,
  ID3D12DescriptorHeap* heap)
:m_num_descriptors(num_descriptors),
 m_next_descriptor_index(0),
 m_descriptor_size(descriptor_size),
 m_heap_size(0),
 m_heap(heap),
 m_cpu_start(cpu_start),
 m_gpu_start(gpu_start)
{
}

void D3D12_DepthStencilDescHeap::GetNextDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE& cpu_handle, D3D12_GPU_DESCRIPTOR_HANDLE& gpu_handle)
{
  cpu_handle.ptr = m_cpu_start.ptr + m_descriptor_size * m_next_descriptor_index;
  gpu_handle.ptr = m_gpu_start.ptr + m_descriptor_size * m_next_descriptor_index;

  ++m_next_descriptor_index;
}

D3D12_DepthStencilDescHeap::~D3D12_DepthStencilDescHeap()
{
  m_heap->Release();
}

ID3D12DescriptorHeap* D3D12_DepthStencilDescHeap::GetHeap() const
{
  return m_heap;
}

UINT D3D12_DepthStencilDescHeap::GetNumInUse() const
{
  return m_num_descriptors;
}

UINT D3D12_DepthStencilDescHeap::GetNumTotal() const
{
  return m_next_descriptor_index;
}
