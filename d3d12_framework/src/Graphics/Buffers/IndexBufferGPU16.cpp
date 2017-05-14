#include "Graphics/Buffers/IndexBufferGPU16.h"
#include "private_inc/D3D12/Buffers/D3D12_IndexBufferGPU16.h"

IndexBufferGPU16* IndexBufferGPU16::CreateD3D12(GraphicsCore& graphics, UINT num)
{
  return D3D12_IndexBufferGPU16::Create(graphics, num);
}

IndexBufferGPU16::IndexBufferGPU16()
{
}

IndexBufferGPU16::~IndexBufferGPU16()
{
}
