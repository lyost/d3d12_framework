#include "Graphics/Buffers/VertexBufferGPU_PositionTextureUV.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionTextureUV.h"

VertexBufferGPU_PositionTextureUV* VertexBufferGPU_PositionTextureUV::CreateD3D12(GraphicsCore& graphics, UINT num)
{
  return D3D12_VertexBufferGPU_PositionTextureUV::Create(graphics, num);
}

VertexBufferGPU_PositionTextureUV::VertexBufferGPU_PositionTextureUV()
{
}

VertexBufferGPU_PositionTextureUV::~VertexBufferGPU_PositionTextureUV()
{
}
