#include "Graphics/Buffers/ReadbackBuffer.h"
#include "private_inc/D3D12/Buffers/D3D12_ReadbackBuffer.h"

ReadbackBuffer* ReadbackBuffer::CreateD3D12(const GraphicsCore& graphics, UINT num_bytes)
{
  return D3D12_ReadbackBuffer::Create(graphics, num_bytes);
}

ReadbackBuffer::ReadbackBuffer()
{
}

ReadbackBuffer::~ReadbackBuffer()
{
}