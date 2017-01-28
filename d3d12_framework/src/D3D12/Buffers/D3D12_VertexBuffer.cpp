#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

void D3D12_VertexBuffer::CreateBuffer(GraphicsCore& graphics, UINT stride, UINT num, const void* data, ID3D12Resource*& buffer, D3D12_VERTEX_BUFFER_VIEW& view)
{
  D3D12_Core& core = (D3D12_Core&)graphics;

  UINT64 num_bytes = num * (UINT64)stride;
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (num_bytes > UINT_MAX)
  {
    throw FrameworkException("Requested size of the vertex buffer is larger than the max number of bytes available in a vertex buffer view");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_HEAP_PROPERTIES heap_prop;
  heap_prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
  heap_prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  heap_prop.CreationNodeMask     = 0;
  heap_prop.VisibleNodeMask      = 0;

  D3D12_RESOURCE_DESC res_desc;
  res_desc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
  res_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  res_desc.Width              = num_bytes;
  res_desc.Height             = 1;
  res_desc.DepthOrArraySize   = 1;
  res_desc.MipLevels          = 1;
  res_desc.Format             = DXGI_FORMAT_UNKNOWN;
  res_desc.SampleDesc.Count   = 1;
  res_desc.SampleDesc.Quality = 0;
  res_desc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  res_desc.Flags              = D3D12_RESOURCE_FLAG_NONE;
  
  HRESULT rc = core.GetDevice()->CreateCommittedResource(&heap_prop, D3D12_HEAP_FLAG_NONE, &res_desc, D3D12_RESOURCE_STATE_GENERIC_READ, NULL, __uuidof(ID3D12Resource),
    (void**)&buffer);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create committed resource for vertex buffer.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }

  void* buffer_data;
  rc = buffer->Map(0, NULL, &buffer_data);
  if (FAILED(rc))
  {
    buffer->Release();

    ostringstream out;
    out << "Failed to map buffer for vertex buffer.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }
  memcpy(buffer_data, data, num * stride);
  buffer->Unmap(0, NULL);

  view.BufferLocation = buffer->GetGPUVirtualAddress();
  view.SizeInBytes    = (UINT)num_bytes; // todo: argument validation to avoid overflow
  view.StrideInBytes  = stride;
}
