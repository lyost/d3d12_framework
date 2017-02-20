#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_ReadbackBuffer.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_ShaderResourceDescHeap.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

D3D12_ReadbackBuffer* D3D12_ReadbackBuffer::Create(const GraphicsCore& graphics, UINT num_bytes)
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(num_bytes, resource_desc);
  D3D12_HEAP_PROPERTIES heap_prop;
  heap_prop.Type                 = D3D12_HEAP_TYPE_READBACK;
  heap_prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  heap_prop.CreationNodeMask     = 0;
  heap_prop.VisibleNodeMask      = 0;

  ID3D12Resource* buffer;
  HRESULT rc = device->CreateCommittedResource(&heap_prop, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_COPY_DEST, NULL, __uuidof(ID3D12Resource), (void**)&buffer);
  if (FAILED(rc))
  {
    throw FrameworkException("Unable to create buffer resource");
  }

  return new D3D12_ReadbackBuffer(buffer, num_bytes);
}

D3D12_ReadbackBuffer::D3D12_ReadbackBuffer(ID3D12Resource* buffer, UINT num_bytes)
:m_buffer(buffer),
 m_host_mem_start(NULL),
 m_num_bytes(num_bytes)
{
}

D3D12_ReadbackBuffer::~D3D12_ReadbackBuffer()
{
  if (m_host_mem_start)
  {
    Unmap();
  }
  m_buffer->Release();
}

ID3D12Resource* D3D12_ReadbackBuffer::GetResource() const
{
  return m_buffer;
}

void D3D12_ReadbackBuffer::Map()
{
  D3D12_RANGE range;
  range.Begin = 0;
  range.End   = 0;
  HRESULT rc  = m_buffer->Map(0, &range, (void**)&m_host_mem_start);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to map readback buffer memory.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }
}

UINT8* D3D12_ReadbackBuffer::GetHostMemStart() const
{
  return m_host_mem_start;
}

void D3D12_ReadbackBuffer::Unmap()
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (!m_host_mem_start)
  {
    throw FrameworkException("Attempting to unmap a readback buffer that isn\'t mapped");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_buffer->Unmap(0, NULL);
  m_host_mem_start = NULL;
}

void D3D12_ReadbackBuffer::GetResourceDesc(UINT& num_bytes, D3D12_RESOURCE_DESC& resource_desc)
{
  resource_desc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
  resource_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  resource_desc.Width              = num_bytes;
  resource_desc.Height             = 1;
  resource_desc.DepthOrArraySize   = 1;
  resource_desc.MipLevels          = 1;
  resource_desc.Format             = DXGI_FORMAT_UNKNOWN;
  resource_desc.SampleDesc.Count   = 1;
  resource_desc.SampleDesc.Quality = 0;
  resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
  resource_desc.Flags              = D3D12_RESOURCE_FLAG_NONE;
}
