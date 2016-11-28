#include "Graphics/HeapArray.h"
#include "private_inc/D3D12/D3D12_HeapArray.h"

HeapArray* HeapArray::CreateD3D12(UINT num_entries)
{
  return D3D12_HeapArray::Create(num_entries);
}

HeapArray::HeapArray()
{
}

HeapArray::~HeapArray()
{
}