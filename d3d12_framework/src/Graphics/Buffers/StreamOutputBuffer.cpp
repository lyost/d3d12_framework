#include "Graphics/Buffers/StreamOutputBuffer.h"
#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBuffer.h"
using namespace std;

StreamOutputBuffer* StreamOutputBuffer::CreateD3D12(GraphicsCore& graphics, const StreamOutputConfig& so_config, UINT stream_index, UINT num_vertices)
{
  return D3D12_StreamOutputBuffer::Create(graphics, so_config, stream_index, num_vertices);
}

void StreamOutputBuffer::GetNumVerticesWrittenD3D12(GraphicsCore& graphics, CommandList& command_list, const vector<StreamOutputBuffer*>& so_buffers, ReadbackBuffer& readback_buffer,
  vector<UINT>& num_vertices)
{
  D3D12_StreamOutputBuffer::GetNumVerticesWritten(graphics, command_list, so_buffers, readback_buffer, num_vertices);
}

StreamOutputBuffer::StreamOutputBuffer()
{
}

StreamOutputBuffer::~StreamOutputBuffer()
{
}
