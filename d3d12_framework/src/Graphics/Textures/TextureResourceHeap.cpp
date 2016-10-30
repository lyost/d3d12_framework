#include "Graphics/Textures/TextureResourceHeap.h"
#include "private_inc/D3D12/Textures/D3D12_TextureResourceHeap.h"

TextureResourceHeap* TextureResourceHeap::CreateD3D12(const GraphicsCore& core, UINT64 num_bytes)
{
  return D3D12_TextureResourceHeap::Create(core, num_bytes);
}

TextureResourceHeap::TextureResourceHeap()
{
}

TextureResourceHeap::~TextureResourceHeap()
{
}
