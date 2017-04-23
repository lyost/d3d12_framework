#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_Custom.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"
#include "FrameworkException.h"
#include "private_inc/BuildSettings.h"
using namespace std;

D3D12_VertexBuffer_Custom* D3D12_VertexBuffer_Custom::Create(GraphicsCore& graphics, UINT num, UINT size, const void* data)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBuffer(graphics, size, num, data, buffer, view);
  return new D3D12_VertexBuffer_Custom(num, buffer, view);
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

void D3D12_VertexBuffer_Custom::Upload(UINT buffer_start_index, const void* data, UINT num_bytes)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
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
  memcpy(((UINT8*)buffer_data) + buffer_start_index, data, num_bytes);
  m_buffer->Unmap(0, NULL);
}

UINT D3D12_VertexBuffer_Custom::GetNumVertices() const
{
  return m_num;
}
