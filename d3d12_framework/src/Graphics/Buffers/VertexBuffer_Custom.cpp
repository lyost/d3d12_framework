#include "Graphics/Buffers/VertexBuffer_Custom.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_Custom.h"

VertexBuffer_Custom* VertexBuffer_Custom::CreateD3D12(GraphicsCore& graphics, UINT num, UINT size, const void* data)
{
  return D3D12_VertexBuffer_Custom::Create(graphics, num, size, data);
}

VertexBuffer_Custom::VertexBuffer_Custom()
{
}

VertexBuffer_Custom::~VertexBuffer_Custom()
{
}
