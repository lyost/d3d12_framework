#include "Graphics/Buffers/StreamOutputBuffer.h"
#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBuffer.h"

StreamOutputBuffer* StreamOutputBuffer::CreateD3D12(GraphicsCore& graphics, const StreamOutputConfig& so_config, UINT stream_index, UINT num_vertices)
{
  return D3D12_StreamOutputBuffer::Create(graphics, so_config, stream_index, num_vertices);
}

StreamOutputBuffer::StreamOutputBuffer()
{
}

StreamOutputBuffer::~StreamOutputBuffer()
{
}
