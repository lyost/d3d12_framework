#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBuffer.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_StreamOutputConfig.h"
#include "private_inc/D3D12/D3D12_CommandList.h"
#include "private_inc/D3D12/Buffers/D3D12_ReadbackBuffer.h"
#include "private_inc/D3D12/Buffers/D3D12_ConstantBuffer.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

StreamOutputBuffer* D3D12_StreamOutputBuffer::Create(GraphicsCore& graphics, const StreamOutputConfig& so_config, UINT stream_index, UINT num_vertices)
{
  D3D12_Core& core = (D3D12_Core&)graphics;
  const D3D12_STREAM_OUTPUT_DESC& config = ((const D3D12_StreamOutputConfig&)so_config).GetDesc();

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (stream_index > config.NumStrides)
  {
    throw FrameworkException("stream_index beyond number of available output streams");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  UINT64 vertex_stride = config.pBufferStrides[stream_index];
  UINT64 num_bytes     = num_vertices * vertex_stride;

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (num_bytes > UINT_MAX)
  {
    throw FrameworkException("Requested size of the stream output buffer is larger than the max number of bytes available in a vertex buffer view");
  }
  if (vertex_stride > UINT_MAX)
  {
    throw FrameworkException("Requested vertex stride in the stream output buffer is larger than the max stride available in a vertex buffer view");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_HEAP_PROPERTIES heap_prop;
  heap_prop.Type                 = D3D12_HEAP_TYPE_DEFAULT;
  heap_prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  heap_prop.CreationNodeMask     = 0;
  heap_prop.VisibleNodeMask      = 0;

  D3D12_RESOURCE_DESC res_desc;
  res_desc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
  res_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  res_desc.Width              = num_bytes + sizeof(UINT64); // note: +sizeof(UINT64) due to graphics card counter for how many bytes it has written to the stream output buffer
  res_desc.Height             = 1;
  res_desc.DepthOrArraySize   = 1;
  res_desc.MipLevels          = 1;
  res_desc.Format             = DXGI_FORMAT_UNKNOWN;
  res_desc.SampleDesc.Count   = 1;
  res_desc.SampleDesc.Quality = 0;
  res_desc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  res_desc.Flags              = D3D12_RESOURCE_FLAG_NONE;
  
  ID3D12Resource* buffer;
  HRESULT rc = core.GetDevice()->CreateCommittedResource(&heap_prop, D3D12_HEAP_FLAG_NONE, &res_desc, D3D12_RESOURCE_STATE_STREAM_OUT, NULL, __uuidof(ID3D12Resource),
    (void**)&buffer);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create committed resource for stream output buffer.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }

  D3D12_STREAM_OUTPUT_BUFFER_VIEW so_view;
  so_view.BufferFilledSizeLocation = buffer->GetGPUVirtualAddress();
  so_view.BufferLocation           = so_view.BufferFilledSizeLocation + sizeof(UINT64);
  so_view.SizeInBytes              = num_bytes;

  D3D12_VERTEX_BUFFER_VIEW vb_view;
  vb_view.BufferLocation = so_view.BufferLocation;
  vb_view.SizeInBytes    = (UINT)num_bytes;
  vb_view.StrideInBytes  = (UINT)vertex_stride;

  return new D3D12_StreamOutputBuffer(buffer, so_view, vb_view, num_vertices);
}

void D3D12_StreamOutputBuffer::GetNumVerticesWritten(GraphicsCore& graphics, CommandList& command_list, const vector<StreamOutputBuffer*>& so_buffers, ReadbackBuffer& readback_buffer,
  vector<UINT>& num_vertices)
{
  D3D12_Core&                core      = (D3D12_Core&)graphics;
  ID3D12GraphicsCommandList* cmd_list  = ((D3D12_CommandList&)command_list).GetCommandList();
  D3D12_ReadbackBuffer&      rb_buffer = (D3D12_ReadbackBuffer&)readback_buffer;
  ID3D12Resource*            resource  = rb_buffer.GetResource();

  command_list.Reset(NULL);

  num_vertices.reserve(num_vertices.size() + so_buffers.size());
  vector<StreamOutputBuffer*>::const_iterator so_it = so_buffers.begin();
  UINT64 dst_offset = 0;
  while (so_it != so_buffers.end())
  {
    D3D12_StreamOutputBuffer* curr_so_buffer = (D3D12_StreamOutputBuffer*)(*so_it);
    cmd_list->CopyBufferRegion(resource, dst_offset, curr_so_buffer->m_buffer, 0, sizeof(UINT64));

    ++so_it;
    dst_offset += sizeof(UINT64);
  }

  command_list.Close();
  core.ExecuteCommandList(command_list);
  core.WaitOnFence();

  rb_buffer.Map();
  UINT64* cbuffer_value = (UINT64*)rb_buffer.GetHostMemStart();
  so_it = so_buffers.begin();
  while (so_it != so_buffers.end())
  {
    D3D12_StreamOutputBuffer* curr_so_buffer = (D3D12_StreamOutputBuffer*)(*so_it);
    num_vertices.push_back((UINT)((*cbuffer_value) / curr_so_buffer->m_vb_view.StrideInBytes));

    ++so_it;
    ++cbuffer_value;
  }
  rb_buffer.Unmap();
}


D3D12_StreamOutputBuffer::D3D12_StreamOutputBuffer(ID3D12Resource* buffer, const D3D12_STREAM_OUTPUT_BUFFER_VIEW& so_view, const D3D12_VERTEX_BUFFER_VIEW& vb_view, UINT num_vertices)
:m_buffer(buffer),
 m_so_view(so_view),
 m_vb_view(vb_view),
 m_num_vertices(num_vertices)
{
}

D3D12_StreamOutputBuffer::~D3D12_StreamOutputBuffer()
{
  m_buffer->Release();
}

UINT D3D12_StreamOutputBuffer::GetVertexCapacity() const
{
  return m_num_vertices;
}

void D3D12_StreamOutputBuffer::PrepReset(CommandList& command_list, ConstantBuffer& scratch_buffer)
{
  ID3D12GraphicsCommandList* cmd_list     = ((D3D12_CommandList&)command_list).GetCommandList();
  D3D12_ConstantBuffer&      const_buffer = (D3D12_ConstantBuffer&)scratch_buffer;
  ID3D12Resource*            resource     = const_buffer.GetResource();

  UINT64 zero = 0;
  const_buffer.Upload((void*)&zero, 0, sizeof(zero));

  D3D12_RESOURCE_BARRIER barrier;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource   = m_buffer;
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_STREAM_OUT;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_COPY_DEST;
  cmd_list->ResourceBarrier(1, &barrier);

  cmd_list->CopyBufferRegion(m_buffer, 0, resource, 0, sizeof(UINT64));
    
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_STREAM_OUT;
  cmd_list->ResourceBarrier(1, &barrier);
}

const D3D12_STREAM_OUTPUT_BUFFER_VIEW& D3D12_StreamOutputBuffer::GetStreamOutputBufferView() const
{
  return m_so_view;
}

const D3D12_VERTEX_BUFFER_VIEW& D3D12_StreamOutputBuffer::GetVertexBufferView() const
{
  return m_vb_view;
}

ID3D12Resource* D3D12_StreamOutputBuffer::GetResource() const
{
  return m_buffer;
}
