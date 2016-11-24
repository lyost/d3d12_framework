#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionColor.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"
#include "FrameworkException.h"

D3D12_VertexBuffer_PositionColor* D3D12_VertexBuffer_PositionColor::Create(GraphicsCore& graphics, UINT num, const Vertex_PositionColor* data)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBuffer(graphics, sizeof(Vertex_PositionColor), num, data, buffer, view);
  return new D3D12_VertexBuffer_PositionColor(num, buffer, view);
}

D3D12_VertexBuffer_PositionColor::D3D12_VertexBuffer_PositionColor(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_VertexBuffer_PositionColor::~D3D12_VertexBuffer_PositionColor()
{
  m_buffer->Release();
}

UINT D3D12_VertexBuffer_PositionColor::GetNumVertices() const
{
  return m_num;
}
