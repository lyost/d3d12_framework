#include "Graphics/Buffers/VertexBufferGPU_Position.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_Position.h"

VertexBufferGPU_Position* VertexBufferGPU_Position::CreateD3D12(GraphicsCore& graphics, UINT num)
{
  return D3D12_VertexBufferGPU_Position::Create(graphics, num);
}

VertexBufferGPU_Position::VertexBufferGPU_Position()
{
}

VertexBufferGPU_Position::~VertexBufferGPU_Position()
{
}
