#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBufferArray.h"
#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBuffer.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

D3D12_StreamOutputBufferArray::D3D12_StreamOutputBufferArray(UINT num_buffers)
:m_num(num_buffers)
{
  m_buffers = new D3D12_STREAM_OUTPUT_BUFFER_VIEW[m_num];
  memset(m_buffers, 0, sizeof(D3D12_STREAM_OUTPUT_BUFFER_VIEW) * m_num);
}

D3D12_StreamOutputBufferArray::~D3D12_StreamOutputBufferArray()
{
  delete [] m_buffers;
}

void D3D12_StreamOutputBufferArray::Set(UINT index, const StreamOutputBuffer& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of stream output buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_StreamOutputBuffer& so_buffer = (const D3D12_StreamOutputBuffer&)buffer;

  m_buffers[index] = so_buffer.GetStreamOutputBufferView();
}

void D3D12_StreamOutputBufferArray::Clear(UINT index)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_buffers[index].BufferLocation           = 0;
  m_buffers[index].SizeInBytes              = 0;
  m_buffers[index].BufferFilledSizeLocation = 0;
}

UINT D3D12_StreamOutputBufferArray::GetNumBuffers() const
{
  return m_num;
}

const D3D12_STREAM_OUTPUT_BUFFER_VIEW* D3D12_StreamOutputBufferArray::GetArray() const
{
  return m_buffers;
}
