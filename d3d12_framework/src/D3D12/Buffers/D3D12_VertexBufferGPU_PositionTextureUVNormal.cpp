#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionTextureUVNormal.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"
#include "FrameworkException.h"
#include "private_inc/BuildSettings.h"
using namespace std;

D3D12_VertexBufferGPU_PositionTextureUVNormal* D3D12_VertexBufferGPU_PositionTextureUVNormal::Create(GraphicsCore& graphics, UINT num)
{
  ID3D12Resource* buffer;
  D3D12_VERTEX_BUFFER_VIEW view;
  D3D12_VertexBuffer::CreateBufferGPU(graphics, sizeof(Vertex_PositionTextureUVNormal), num, buffer, view);
  return new D3D12_VertexBufferGPU_PositionTextureUVNormal(num, buffer, view);
}

D3D12_VertexBufferGPU_PositionTextureUVNormal::D3D12_VertexBufferGPU_PositionTextureUVNormal(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_VertexBufferGPU_PositionTextureUVNormal::~D3D12_VertexBufferGPU_PositionTextureUVNormal()
{
  m_buffer->Release();
}

UINT D3D12_VertexBufferGPU_PositionTextureUVNormal::GetNumVertices() const
{
  return m_num;
}

ID3D12Resource* D3D12_VertexBufferGPU_PositionTextureUVNormal::GetResource() const
{
  return m_buffer;
}
