#include "Graphics/Buffers/ConstantBuffer.h"
#include "private_inc/D3D12/Buffers/D3D12_ConstantBuffer.h"

ConstantBuffer* ConstantBuffer::CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT num_bytes)
{
  return D3D12_ConstantBuffer::Create(graphics, shader_buffer_heap, num_bytes);
}

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
}