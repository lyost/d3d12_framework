#include "Graphics/Buffers/ConstantBuffer.h"
#include "private_inc/D3D12/Buffers/D3D12_ConstantBuffer.h"

UINT ConstantBuffer::GetAlignedSize(const GraphicsCore& graphics, UINT num_bytes)
{
  return D3D12_ConstantBuffer::GetAlignedSize(graphics, num_bytes);
}

ConstantBuffer* ConstantBuffer::CreateD3D12(const GraphicsCore& graphics, BufferResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT num_bytes)
{
  return D3D12_ConstantBuffer::Create(graphics, resource_heap, shader_buffer_heap, num_bytes);
}

ConstantBuffer::ConstantBuffer()
{
}

ConstantBuffer::~ConstantBuffer()
{
}