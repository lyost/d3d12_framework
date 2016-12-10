#include "Graphics/Buffers/VertexBuffer_PositionTexture.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTexture.h"

VertexBuffer_PositionTexture* VertexBuffer_PositionTexture::CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureU* data)
{
  return D3D12_VertexBuffer_PositionTexture::Create(graphics, num, data);
}

VertexBuffer_PositionTexture* VertexBuffer_PositionTexture::CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUV* data)
{
  return D3D12_VertexBuffer_PositionTexture::Create(graphics, num, data);
}

VertexBuffer_PositionTexture* VertexBuffer_PositionTexture::CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUVW* data)
{
  return D3D12_VertexBuffer_PositionTexture::Create(graphics, num, data);
}

VertexBuffer_PositionTexture::VertexBuffer_PositionTexture()
{
}

VertexBuffer_PositionTexture::~VertexBuffer_PositionTexture()
{
}
