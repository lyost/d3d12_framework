#include <sstream>
#include "private_inc/D3D12/D3D12_ShaderResourceDescHeap.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

// todo: add class for D3D12_ShaderSamplerHeap

D3D12_ShaderResourceDescHeap* D3D12_ShaderResourceDescHeap::Create(const GraphicsCore& graphics, UINT num_descriptors)
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  D3D12_DESCRIPTOR_HEAP_DESC desc;
  desc.Type           = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
  desc.NumDescriptors = num_descriptors;
  desc.Flags          = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
  desc.NodeMask       = 0;

  ID3D12DescriptorHeap* heap = NULL;
  HRESULT rc = device->CreateDescriptorHeap(&desc, __uuidof(ID3D12DescriptorHeap), (void**)&heap);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create descriptor heap for shader buffers.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }

  UINT increment_size = device->GetDescriptorHandleIncrementSize(desc.Type);

  D3D12_CPU_DESCRIPTOR_HANDLE cpu_start = heap->GetCPUDescriptorHandleForHeapStart();
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_start = heap->GetGPUDescriptorHandleForHeapStart();

  return new D3D12_ShaderResourceDescHeap(num_descriptors, cpu_start, gpu_start, increment_size, heap);
}

D3D12_ShaderResourceDescHeap::D3D12_ShaderResourceDescHeap(UINT num_descriptors, const D3D12_CPU_DESCRIPTOR_HANDLE& cpu_start, const D3D12_GPU_DESCRIPTOR_HANDLE& gpu_start, UINT descriptor_size,
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

void D3D12_ShaderResourceDescHeap::GetNextDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE& cpu_handle, D3D12_GPU_DESCRIPTOR_HANDLE& gpu_handle)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (m_next_descriptor_index >= m_num_descriptors)
  {
    throw FrameworkException("No descriptors available");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  cpu_handle.ptr = m_cpu_start.ptr + m_descriptor_size * m_next_descriptor_index;
  gpu_handle.ptr = m_gpu_start.ptr + m_descriptor_size * m_next_descriptor_index;

  ++m_next_descriptor_index;
}

D3D12_ShaderResourceDescHeap::~D3D12_ShaderResourceDescHeap()
{
  m_heap->Release();
}

ID3D12DescriptorHeap* D3D12_ShaderResourceDescHeap::GetHeap() const
{
  return m_heap;
}

UINT D3D12_ShaderResourceDescHeap::GetNumInUse() const
{
  return m_num_descriptors;
}

UINT D3D12_ShaderResourceDescHeap::GetNumTotal() const
{
  return m_next_descriptor_index;
}
