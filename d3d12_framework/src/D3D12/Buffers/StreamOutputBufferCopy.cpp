#include "Graphics/Buffers/StreamOutputBufferCopy.h"

StreamOutputBufferCopy* StreamOutputBufferCopy::Create(D3D11_Core& graphics,
  const StreamOutputBufferDesc& desc,UINT num)
{
  UINT stride = desc.GetStride();
  ID3D11Buffer* output_buffer = CreateBuffer(graphics,num,stride,false);
  if (output_buffer == NULL)
  {
    return NULL;
  }
  ID3D11Buffer* host_buffer = CreateBuffer(graphics,num,stride,true);
  if (host_buffer == NULL)
  {
    output_buffer->Release();
    return NULL;
  }
  
  return new StreamOutputBufferCopy(output_buffer,num,stride,desc.GetSlot(),
    host_buffer);
}

StreamOutputBufferCopy::StreamOutputBufferCopy(ID3D11Buffer* buffer,UINT num,
  UINT stride,UINT slot,ID3D11Buffer* host_buffer)
:StreamOutputBuffer(buffer,num,stride,slot),
 m_host_buffer(host_buffer)
{
}

StreamOutputBufferCopy::~StreamOutputBufferCopy()
{
 m_host_buffer->Release();
}

void* StreamOutputBufferCopy::StartCopy(ID3D11DeviceContext* context) const
{
  context->CopyResource(m_host_buffer,m_buffer);
  D3D11_MAPPED_SUBRESOURCE res;
  if (FAILED(context->Map(m_host_buffer,0,D3D11_MAP_READ,0,&res)))
  {
    return NULL;
  }
  
  return res.pData;
}

void StreamOutputBufferCopy::EndCopy(ID3D11DeviceContext* context) const
{
  context->Unmap(m_host_buffer,0);
}
