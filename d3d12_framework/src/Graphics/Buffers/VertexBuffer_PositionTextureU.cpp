#include "Graphics/Buffers/VertexBuffer_PositionTextureU.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTextureU.h"

VertexBuffer_PositionTextureU* VertexBuffer_PositionTextureU::CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureU* data)
{
  return D3D12_VertexBuffer_PositionTextureU::Create(graphics, num, data);
}

VertexBuffer_PositionTextureU::VertexBuffer_PositionTextureU()
{
}

VertexBuffer_PositionTextureU::~VertexBuffer_PositionTextureU()
{
}
