#include "Graphics/Buffers/VertexBuffer_PositionTextureUV.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTextureUV.h"

VertexBuffer_PositionTextureUV* VertexBuffer_PositionTextureUV::CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUV* data)
{
  return D3D12_VertexBuffer_PositionTextureUV::Create(graphics, num, data);
}

VertexBuffer_PositionTextureUV::VertexBuffer_PositionTextureUV()
{
}

VertexBuffer_PositionTextureUV::~VertexBuffer_PositionTextureUV()
{
}
