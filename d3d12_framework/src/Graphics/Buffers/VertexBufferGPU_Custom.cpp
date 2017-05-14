#include "Graphics/Buffers/VertexBufferGPU_Custom.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_Custom.h"

VertexBufferGPU_Custom* VertexBufferGPU_Custom::CreateD3D12(GraphicsCore& graphics, UINT num, UINT size)
{
  return D3D12_VertexBufferGPU_Custom::Create(graphics, num, size);
}

VertexBufferGPU_Custom::VertexBufferGPU_Custom()
{
}

VertexBufferGPU_Custom::~VertexBufferGPU_Custom()
{
}
