#include "Graphics/Buffers/StreamOutputBuffer.h"
#include "log.h"

StreamOutputBuffer* StreamOutputBuffer::Create(D3D11_Core& graphics,
  const StreamOutputBufferDesc& desc,UINT num)
{
  UINT stride = desc.GetStride();
  ID3D11Buffer* tmp = CreateBuffer(graphics,num,stride,false);
  if (tmp == NULL)
  {
    return NULL;
  }
  
  return new StreamOutputBuffer(tmp,num,stride,desc.GetSlot());
}

StreamOutputBuffer::StreamOutputBuffer(ID3D11Buffer* buffer,UINT num,
  UINT stride,UINT slot)
:m_buffer(buffer),
 m_num(num),
 m_stride(stride),
 m_slot(slot)
{
}

StreamOutputBuffer::~StreamOutputBuffer()
{
  m_buffer->Release();
}

void StreamOutputBuffer::MakeActive(ID3D11DeviceContext* context)
{
  UINT stride = GetStride();
  UINT offset = 0;
  context->IASetVertexBuffers(0,1,&m_buffer,&stride,&offset);
}

UINT StreamOutputBuffer::GetNumEntries() const
{
  return m_num;
}

UINT StreamOutputBuffer::GetStride() const
{
  return m_stride;
}

UINT StreamOutputBuffer::GetSlot() const
{
  return m_slot;
}

ID3D11Buffer* StreamOutputBuffer::GetBuffer() const
{
  return m_buffer;
}

ID3D11Buffer* StreamOutputBuffer::CreateBuffer(D3D11_Core& graphics,UINT num,
  UINT size,bool host)
{
  ID3D11Buffer* back = NULL;
  
  ID3D11Device* device = graphics.GetDevice();
  
  D3D11_BUFFER_DESC bd;
  ZeroMemory(&bd,sizeof(bd));
  bd.ByteWidth = num * size;
  if (host)
  {
    bd.Usage          = D3D11_USAGE_STAGING;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_READ;
    bd.BindFlags      = 0;
  }
  else
  {
    bd.Usage          = D3D11_USAGE_DEFAULT;
    bd.CPUAccessFlags = 0;
    bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER|D3D11_BIND_STREAM_OUTPUT;
  }
  if (FAILED(device->CreateBuffer(&bd,NULL,&back)))
  {
    log_print("Failed to create stream output buffer");
    return NULL;
  }
  
  return back;
}
