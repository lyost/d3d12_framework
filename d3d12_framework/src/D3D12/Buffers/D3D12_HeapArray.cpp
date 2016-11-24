#include "private_inc/D3D12/Buffers/D3D12_HeapArray.h"
#include "private_inc/D3D12/Buffers/D3D12_ShaderResourceDescHeap.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

HeapArray* D3D12_HeapArray::Create(UINT num_entries)
{
  return new D3D12_HeapArray(num_entries);
}

D3D12_HeapArray::D3D12_HeapArray(UINT num_entries)
:m_len(num_entries)
{
  m_heaps = new ID3D12DescriptorHeap*[num_entries];
  memset((void*)m_heaps, 0, sizeof(ID3D12DescriptorHeap*) * num_entries);
}

D3D12_HeapArray::~D3D12_HeapArray()
{
  for (UINT i = 0; i < m_len; i++)
  {
    if (m_heaps[i])
    {
      m_heaps[i]->Release();
    }
  }

  delete [] m_heaps;
}

void D3D12_HeapArray::SetHeap(UINT index, const ShaderResourceDescHeap& heap)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_len)
  {
    throw new FrameworkException("index beyond number of heap entries");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  if (m_heaps[index])
  {
    m_heaps[index]->Release();
  }

  const D3D12_ShaderResourceDescHeap& d3d12_heap = (const D3D12_ShaderResourceDescHeap&)heap;
  ID3D12DescriptorHeap* desc = d3d12_heap.GetHeap();
  desc->AddRef();
  m_heaps[index] = desc;
}

UINT D3D12_HeapArray::GetLength() const
{
  return m_len;
}

ID3D12DescriptorHeap** D3D12_HeapArray::GetArray() const
{
  return m_heaps;
}
