#include "Graphics/Buffers/VertexBuffer_Position.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_Position.h"

VertexBuffer_Position* VertexBuffer_Position::CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_Position* data)
{
  return D3D12_VertexBuffer_Position::Create(graphics, num, data);
}

VertexBuffer_Position::VertexBuffer_Position()
{
}

VertexBuffer_Position::~VertexBuffer_Position()
{
}
