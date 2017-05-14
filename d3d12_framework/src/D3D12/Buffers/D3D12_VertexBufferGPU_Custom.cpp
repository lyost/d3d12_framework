#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_Custom.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"
#include "FrameworkException.h"
#include "private_inc/BuildSettings.h"
using namespace std;

D3D12_VertexBufferGPU_Custom* D3D12_VertexBufferGPU_Custom::Create(GraphicsCore& graphics, UINT num, UINT size)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBufferGPU(graphics, size, num,  buffer, view);
  return new D3D12_VertexBufferGPU_Custom(num, buffer, view);
}

D3D12_VertexBufferGPU_Custom::D3D12_VertexBufferGPU_Custom(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_VertexBufferGPU_Custom::~D3D12_VertexBufferGPU_Custom()
{
  m_buffer->Release();
}

UINT D3D12_VertexBufferGPU_Custom::GetNumVertices() const
{
  return m_num;
}

ID3D12Resource* D3D12_VertexBufferGPU_Custom::GetResource() const
{
  return m_buffer;
}
