#include "Graphics/Buffers/VertexBufferGPU_PositionTextureUVNormal.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionTextureUVNormal.h"

VertexBufferGPU_PositionTextureUVNormal* VertexBufferGPU_PositionTextureUVNormal::CreateD3D12(GraphicsCore& graphics, UINT num)
{
  return D3D12_VertexBufferGPU_PositionTextureUVNormal::Create(graphics, num);
}

VertexBufferGPU_PositionTextureUVNormal::VertexBufferGPU_PositionTextureUVNormal()
{
}

VertexBufferGPU_PositionTextureUVNormal::~VertexBufferGPU_PositionTextureUVNormal()
{
}
