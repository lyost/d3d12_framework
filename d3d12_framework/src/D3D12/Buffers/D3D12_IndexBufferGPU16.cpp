#include "private_inc/D3D12/Buffers/D3D12_IndexBufferGPU16.h"
#include "private_inc/D3D12/Buffers/D3D12_IndexBuffer.h"

D3D12_IndexBufferGPU16* D3D12_IndexBufferGPU16::Create(GraphicsCore& graphics, UINT num)
{
  ID3D12Resource* buffer;
  D3D12_INDEX_BUFFER_VIEW view;
  D3D12_IndexBuffer::CreateBufferGPU(graphics, sizeof(WORD), DXGI_FORMAT_R16_UINT, num, buffer, view);
  return new D3D12_IndexBufferGPU16(num, buffer, view);
}

D3D12_IndexBufferGPU16::D3D12_IndexBufferGPU16(UINT num, ID3D12Resource* buffer, D3D12_INDEX_BUFFER_VIEW& view)
:m_num(num),
 m_buffer(buffer),
 m_view(view)
{
}

D3D12_IndexBufferGPU16::~D3D12_IndexBufferGPU16()
{
  m_buffer->Release();
}

UINT D3D12_IndexBufferGPU16::GetNumIndices() const
{
  return m_num;
}

const D3D12_INDEX_BUFFER_VIEW& D3D12_IndexBufferGPU16::GetBuffer() const
{
  return m_view;
}

ID3D12Resource* D3D12_IndexBufferGPU16::GetResource() const
{
  return m_buffer;
}
