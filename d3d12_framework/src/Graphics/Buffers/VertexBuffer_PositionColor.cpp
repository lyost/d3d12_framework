#include "Graphics/Buffers/VertexBuffer_PositionColor.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionColor.h"

VertexBuffer_PositionColor* VertexBuffer_PositionColor::CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionColor* data)
{
  return D3D12_VertexBuffer_PositionColor::Create(graphics, num, data);
}

VertexBuffer_PositionColor::VertexBuffer_PositionColor()
{
}

VertexBuffer_PositionColor::~VertexBuffer_PositionColor()
{
}
