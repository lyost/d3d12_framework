#include <cassert>
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferArray.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_Custom.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTexture.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionColor.h"
#include "log.h"
using namespace std;

D3D12_VertexBufferArray::D3D12_VertexBufferArray(UINT num_buffers)
:m_num(num_buffers)
{
  m_vertex_buffers = new D3D12_VERTEX_BUFFER_VIEW[m_num];
  memset(m_vertex_buffers, 0, sizeof(D3D12_VERTEX_BUFFER_VIEW*) * m_num);
}

D3D12_VertexBufferArray::~D3D12_VertexBufferArray()
{
  delete [] m_vertex_buffers;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBuffer_Custom& buffer)
{
  assert(index <= m_num);

  const D3D12_VertexBuffer_Custom& vertex_buffer = (const D3D12_VertexBuffer_Custom&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBuffer_PositionTexture& buffer)
{
  assert(index <= m_num);

  const D3D12_VertexBuffer_PositionTexture& vertex_buffer = (const D3D12_VertexBuffer_PositionTexture&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBuffer_PositionColor& buffer)
{
  assert(index <= m_num);

  const D3D12_VertexBuffer_PositionColor& vertex_buffer = (const D3D12_VertexBuffer_PositionColor&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Clear(UINT index)
{
  assert(index <= m_num);

  m_vertex_buffers[index].BufferLocation = 0;
  m_vertex_buffers[index].SizeInBytes    = 0;
  m_vertex_buffers[index].StrideInBytes  = 0;
}

UINT D3D12_VertexBufferArray::GetNumBuffers() const
{
  return m_num;
}

const D3D12_VERTEX_BUFFER_VIEW* D3D12_VertexBufferArray::GetArray() const
{
  return m_vertex_buffers;
}
