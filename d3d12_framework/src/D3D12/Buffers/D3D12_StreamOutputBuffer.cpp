#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBuffer.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_StreamOutputConfig.h"
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
  res_desc.Width              = num_bytes + sizeof(UINT64); // note: +sizeof(UINT64) due to despite https://msdn.microsoft.com/en-us/library/windows/desktop/dn903944%28v=vs.85%29.aspx documenting it as a 32bit field, 64bits is required
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
  so_view.BufferLocation           = buffer->GetGPUVirtualAddress();
  so_view.SizeInBytes              = num_bytes;
  so_view.BufferFilledSizeLocation = so_view.BufferLocation + so_view.SizeInBytes;

  D3D12_VERTEX_BUFFER_VIEW vb_view;
  vb_view.BufferLocation = so_view.BufferLocation;
  vb_view.SizeInBytes    = (UINT)num_bytes;
  vb_view.StrideInBytes  = (UINT)vertex_stride;

  return new D3D12_StreamOutputBuffer(buffer, so_view, vb_view, num_vertices);
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
