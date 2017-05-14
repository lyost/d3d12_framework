#include "Graphics/Buffers/VertexBuffer_PositionTextureUVW.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTextureUVW.h"

VertexBuffer_PositionTextureUVW* VertexBuffer_PositionTextureUVW::CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUVW* data)
{
  return D3D12_VertexBuffer_PositionTextureUVW::Create(graphics, num, data);
}

VertexBuffer_PositionTextureUVW::VertexBuffer_PositionTextureUVW()
{
}

VertexBuffer_PositionTextureUVW::~VertexBuffer_PositionTextureUVW()
{
}
