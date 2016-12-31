#include "Graphics/Textures/TextureCube.h"
#include "private_inc/D3D12/Textures/D3D12_TextureCube.h"

TextureCube* TextureCube::CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format)
{
  return D3D12_TextureCube::Create(graphics, shader_buffer_heap, width, height, format);
}

TextureCube::TextureCube()
{
}

TextureCube::~TextureCube()
{
}
