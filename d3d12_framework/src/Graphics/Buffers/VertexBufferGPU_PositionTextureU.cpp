#include "Graphics/Buffers/VertexBufferGPU_PositionTextureU.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionTextureU.h"

VertexBufferGPU_PositionTextureU* VertexBufferGPU_PositionTextureU::CreateD3D12(GraphicsCore& graphics, UINT num)
{
  return D3D12_VertexBufferGPU_PositionTextureU::Create(graphics, num);
}

VertexBufferGPU_PositionTextureU::VertexBufferGPU_PositionTextureU()
{
}

VertexBufferGPU_PositionTextureU::~VertexBufferGPU_PositionTextureU()
{
}
