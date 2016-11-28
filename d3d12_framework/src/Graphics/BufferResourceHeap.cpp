#include "Graphics/BufferResourceHeap.h"
#include "private_inc/D3D12/D3D12_BufferResourceHeap.h"

BufferResourceHeap* BufferResourceHeap::CreateD3D12(const GraphicsCore& core, UINT64 num_bytes)
{
  return D3D12_BufferResourceHeap::Create(core, num_bytes);
}

BufferResourceHeap::BufferResourceHeap()
{
}

BufferResourceHeap::~BufferResourceHeap()
{
}
