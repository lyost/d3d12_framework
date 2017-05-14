#include "Graphics/Buffers/VertexBufferGPU_PositionTextureUVW.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionTextureUVW.h"

VertexBufferGPU_PositionTextureUVW* VertexBufferGPU_PositionTextureUVW::CreateD3D12(GraphicsCore& graphics, UINT num)
{
  return D3D12_VertexBufferGPU_PositionTextureUVW::Create(graphics, num);
}

VertexBufferGPU_PositionTextureUVW::VertexBufferGPU_PositionTextureUVW()
{
}

VertexBufferGPU_PositionTextureUVW::~VertexBufferGPU_PositionTextureUVW()
{
}
