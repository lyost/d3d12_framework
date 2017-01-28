#include "Graphics/Buffers/StreamOutputBufferArray.h"
#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBufferArray.h"
#include "log.h"

StreamOutputBufferArray* StreamOutputBufferArray::CreateD3D12(UINT num_buffers)
{
  return new D3D12_StreamOutputBufferArray(num_buffers);
}

StreamOutputBufferArray::StreamOutputBufferArray()
{
}

StreamOutputBufferArray::~StreamOutputBufferArray()
{
}
