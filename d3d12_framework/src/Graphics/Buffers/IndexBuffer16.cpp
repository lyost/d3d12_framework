#include "Graphics/Buffers/IndexBuffer16.h"
#include "private_inc/D3D12/Buffers/D3D12_IndexBuffer16.h"

IndexBuffer16* IndexBuffer16::CreateD3D12(GraphicsCore& graphics, UINT num, const WORD* data)
{
  return D3D12_IndexBuffer16::Create(graphics, num, data);
}

IndexBuffer16::IndexBuffer16()
{
}

IndexBuffer16::~IndexBuffer16()
{
}
