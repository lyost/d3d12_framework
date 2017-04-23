#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTexture.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"
#include "FrameworkException.h"
#include "private_inc/BuildSettings.h"
using namespace std;

D3D12_VertexBuffer_PositionTexture* D3D12_VertexBuffer_PositionTexture::Create(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureU* data)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBuffer(graphics, sizeof(Vertex_PositionTextureU), num, data, buffer, view);
  return new D3D12_VertexBuffer_PositionTexture(num, buffer, view, TEXTURE_TYPE_U);
}

D3D12_VertexBuffer_PositionTexture* D3D12_VertexBuffer_PositionTexture::Create(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUV* data)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBuffer(graphics, sizeof(Vertex_PositionTextureUV), num, data, buffer, view);
  return new D3D12_VertexBuffer_PositionTexture(num, buffer, view, TEXTURE_TYPE_UV);
}

D3D12_VertexBuffer_PositionTexture* D3D12_VertexBuffer_PositionTexture::Create(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUVW* data)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBuffer(graphics, sizeof(Vertex_PositionTextureUVW), num, data, buffer, view);
  return new D3D12_VertexBuffer_PositionTexture(num, buffer, view, TEXTURE_TYPE_UVW);
}

D3D12_VertexBuffer_PositionTexture::D3D12_VertexBuffer_PositionTexture(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view, TextureType type)
:m_num(num),
 m_buffer(buffer),
 m_view(view),
 m_type(type)
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

void D3D12_VertexBuffer_PositionTexture::Upload(UINT buffer_start_index, const Vertex_PositionTextureU* data, UINT num_entries)
{
  const UINT num_bytes = num_entries * sizeof(Vertex_PositionTextureU);

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (m_type != TEXTURE_TYPE_U)
  {
    throw FrameworkException("Attempting to send incorrect texture type data to a Vertex_PositionTextureU vertex buffer");
  }
  if ((buffer_start_index + num_bytes) > m_buffer->GetDesc().Width)
  {
    throw FrameworkException("Attempting to upload beyond the end of the vertex buffer");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  void* buffer_data;
  HRESULT rc = m_buffer->Map(0, NULL, &buffer_data);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to map buffer for vertex buffer.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }
  memcpy(((Vertex_PositionTextureU*)buffer_data) + buffer_start_index, data, num_bytes);
  m_buffer->Unmap(0, NULL);
}

void D3D12_VertexBuffer_PositionTexture::Upload(UINT buffer_start_index, const Vertex_PositionTextureUV* data, UINT num_entries)
{
  const UINT num_bytes = num_entries * sizeof(Vertex_PositionTextureUV);

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (m_type != TEXTURE_TYPE_UV)
  {
    throw FrameworkException("Attempting to send incorrect texture type data to a Vertex_PositionTextureUV vertex buffer");
  }
  if ((buffer_start_index + num_bytes) > m_buffer->GetDesc().Width)
  {
    throw FrameworkException("Attempting to upload beyond the end of the vertex buffer");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  void* buffer_data;
  HRESULT rc = m_buffer->Map(0, NULL, &buffer_data);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to map buffer for vertex buffer.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }
  memcpy(((Vertex_PositionTextureUV*)buffer_data) + buffer_start_index, data, num_bytes);
  m_buffer->Unmap(0, NULL);
}

void D3D12_VertexBuffer_PositionTexture::Upload(UINT buffer_start_index, const Vertex_PositionTextureUVW* data, UINT num_entries)
{
  const UINT num_bytes = num_entries * sizeof(Vertex_PositionTextureUVW);

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (m_type != TEXTURE_TYPE_UVW)
  {
    throw FrameworkException("Attempting to send incorrect texture type data to a Vertex_PositionTextureUVW vertex buffer");
  }
  if ((buffer_start_index + num_bytes) > m_buffer->GetDesc().Width)
  {
    throw FrameworkException("Attempting to upload beyond the end of the vertex buffer");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  void* buffer_data;
  HRESULT rc = m_buffer->Map(0, NULL, &buffer_data);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to map buffer for vertex buffer.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }
  memcpy(((Vertex_PositionTextureUVW*)buffer_data) + buffer_start_index, data, num_bytes);
  m_buffer->Unmap(0, NULL);
}
