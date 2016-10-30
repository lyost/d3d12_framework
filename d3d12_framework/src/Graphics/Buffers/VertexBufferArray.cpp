#include "Graphics/Buffers/VertexBufferArray.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferArray.h"
#include "log.h"

VertexBufferArray* VertexBufferArray::CreateD3D12(UINT num_buffers)
{
  return new D3D12_VertexBufferArray(num_buffers);
}

VertexBufferArray::VertexBufferArray()
{
}

VertexBufferArray::~VertexBufferArray()
{
}
