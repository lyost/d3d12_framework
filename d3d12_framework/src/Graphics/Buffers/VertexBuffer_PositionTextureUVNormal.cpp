#include "Graphics/Buffers/VertexBuffer_PositionTextureUVNormal.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTextureUVNormal.h"

VertexBuffer_PositionTextureUVNormal* VertexBuffer_PositionTextureUVNormal::CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUVNormal* data)
{
  return D3D12_VertexBuffer_PositionTextureUVNormal::Create(graphics, num, data);
}

VertexBuffer_PositionTextureUVNormal::VertexBuffer_PositionTextureUVNormal()
{
}

VertexBuffer_PositionTextureUVNormal::~VertexBuffer_PositionTextureUVNormal()
{
}
