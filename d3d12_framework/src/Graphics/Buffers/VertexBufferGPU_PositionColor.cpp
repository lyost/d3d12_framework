#include "Graphics/Buffers/VertexBufferGPU_PositionColor.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionColor.h"

VertexBufferGPU_PositionColor* VertexBufferGPU_PositionColor::CreateD3D12(GraphicsCore& graphics, UINT num)
{
  return D3D12_VertexBufferGPU_PositionColor::Create(graphics, num);
}

VertexBufferGPU_PositionColor::VertexBufferGPU_PositionColor()
{
}

VertexBufferGPU_PositionColor::~VertexBufferGPU_PositionColor()
{
}
