#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionColor.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"
#include "FrameworkException.h"
#include "private_inc/BuildSettings.h"
using namespace std;

D3D12_VertexBufferGPU_PositionColor* D3D12_VertexBufferGPU_PositionColor::Create(GraphicsCore& graphics, UINT num)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBufferGPU(graphics, sizeof(Vertex_PositionColor), num, buffer, view);
  return new D3D12_VertexBufferGPU_PositionColor(num, buffer, view);
}

D3D12_VertexBufferGPU_PositionColor::D3D12_VertexBufferGPU_PositionColor(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_VertexBufferGPU_PositionColor::~D3D12_VertexBufferGPU_PositionColor()
{
  m_buffer->Release();
}

UINT D3D12_VertexBufferGPU_PositionColor::GetNumVertices() const
{
  return m_num;
}

ID3D12Resource* D3D12_VertexBufferGPU_PositionColor::GetResource() const
{
  return m_buffer;
}
