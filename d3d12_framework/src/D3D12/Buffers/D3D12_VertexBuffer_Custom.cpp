#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_Custom.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"

D3D12_VertexBuffer_Custom* D3D12_VertexBuffer_Custom::Create(GraphicsCore& graphics, UINT num, UINT size, const void* data)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  if (D3D12_VertexBuffer::CreateBuffer(graphics, size, num, data, buffer, view))
  {
    return new D3D12_VertexBuffer_Custom(num, buffer, view);
  }
  else
  {
    return NULL;
  }
}

D3D12_VertexBuffer_Custom::D3D12_VertexBuffer_Custom(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_VertexBuffer_Custom::~D3D12_VertexBuffer_Custom()
{
  m_buffer->Release();
}

UINT D3D12_VertexBuffer_Custom::GetNumVertices() const
{
  return m_num;
}
