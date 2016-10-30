#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTexture.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"

D3D12_VertexBuffer_PositionTexture* D3D12_VertexBuffer_PositionTexture::Create(GraphicsCore& graphics, UINT num, const Vertex_PositionTexture* data)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  if (D3D12_VertexBuffer::CreateBuffer(graphics, sizeof(Vertex_PositionTexture), num, data, buffer, view))
  {
    return new D3D12_VertexBuffer_PositionTexture(num, buffer, view);
  }
  else
  {
    return NULL;
  }
}

D3D12_VertexBuffer_PositionTexture::D3D12_VertexBuffer_PositionTexture(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_VertexBuffer_PositionTexture::~D3D12_VertexBuffer_PositionTexture()
{
  m_buffer->Release();
}

UINT D3D12_VertexBuffer_PositionTexture::GetNumVertices() const
{
  return m_num;
}
