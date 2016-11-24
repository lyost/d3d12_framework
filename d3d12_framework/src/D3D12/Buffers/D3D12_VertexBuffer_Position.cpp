#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_Position.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"
#include "FrameworkException.h"

D3D12_VertexBuffer_Position* D3D12_VertexBuffer_Position::Create(GraphicsCore& graphics, UINT num, const Vertex_Position* data)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBuffer(graphics, sizeof(Vertex_Position), num, data, buffer, view);
  return new D3D12_VertexBuffer_Position(num, buffer, view);
}

D3D12_VertexBuffer_Position::D3D12_VertexBuffer_Position(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_VertexBuffer_Position::~D3D12_VertexBuffer_Position()
{
  m_buffer->Release();
}

UINT D3D12_VertexBuffer_Position::GetNumVertices() const
{
  return m_num;
}
