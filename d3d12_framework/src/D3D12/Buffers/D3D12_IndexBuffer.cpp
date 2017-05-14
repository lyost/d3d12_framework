#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_IndexBuffer.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_CommandList.h"
#include "FrameworkException.h"
using namespace std;

void CreateBuffer(GraphicsCore& graphics, D3D12_HEAP_PROPERTIES heap_prop, UINT stride, DXGI_FORMAT format, UINT num, ID3D12Resource*& buffer, D3D12_INDEX_BUFFER_VIEW& view)
{
  D3D12_Core& core = (D3D12_Core&)graphics;

  D3D12_RESOURCE_DESC res_desc;
  res_desc.Dimension          = D3D12_RESOURCE_DIMENSION_BUFFER;
  res_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  res_desc.Width              = num * stride;
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
    out << "Failed to create committed resource for index buffer.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }

  view.BufferLocation = buffer->GetGPUVirtualAddress();
  view.SizeInBytes = num * stride;
  view.Format = format;
}

void D3D12_IndexBuffer::CreateBuffer(GraphicsCore& graphics, UINT stride, DXGI_FORMAT format, UINT num, const void* data, ID3D12Resource*& buffer, D3D12_INDEX_BUFFER_VIEW& view)
{
  D3D12_HEAP_PROPERTIES heap_prop;
  heap_prop.Type                 = D3D12_HEAP_TYPE_UPLOAD;
  heap_prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  heap_prop.CreationNodeMask     = 0;
  heap_prop.VisibleNodeMask      = 0;

  CreateBuffer(graphics, heap_prop, stride, format, num, buffer, view);

  void* buffer_data;
  HRESULT rc = buffer->Map(0, NULL, &buffer_data);
  if (FAILED(rc))
  {
    buffer->Release();

    ostringstream out;
    out << "Failed to map buffer for index buffer.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }
  memcpy(buffer_data, data, num * stride);
  buffer->Unmap(0, NULL);
}

void D3D12_IndexBuffer::CreateBufferGPU(GraphicsCore& graphics, UINT stride, DXGI_FORMAT format, UINT num, ID3D12Resource*& buffer, D3D12_INDEX_BUFFER_VIEW& view)
{
  D3D12_HEAP_PROPERTIES heap_prop;
  heap_prop.Type                 = D3D12_HEAP_TYPE_DEFAULT;
  heap_prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  heap_prop.CreationNodeMask     = 0;
  heap_prop.VisibleNodeMask      = 0;

  CreateBuffer(graphics, heap_prop, stride, format, num, buffer, view);
}

void D3D12_IndexBuffer::PrepUpload(GraphicsCore& graphics, CommandList& command_list, ID3D12Resource* src, ID3D12Resource* dst)
{
  ID3D12Device*              device   = ((D3D12_Core&)graphics).GetDevice();
  ID3D12GraphicsCommandList* cmd_list = ((D3D12_CommandList&)command_list).GetCommandList();

  D3D12_RESOURCE_BARRIER prep_copy;
  prep_copy.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  prep_copy.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  prep_copy.Transition.pResource   = dst;
  prep_copy.Transition.Subresource = 0;
  prep_copy.Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
  prep_copy.Transition.StateAfter  = D3D12_RESOURCE_STATE_COPY_DEST;
  cmd_list->ResourceBarrier(1, &prep_copy);

  cmd_list->CopyResource(dst, src);

  D3D12_RESOURCE_BARRIER done_copy;
  done_copy.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  done_copy.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  done_copy.Transition.pResource   = dst;
  done_copy.Transition.Subresource = 0;
  done_copy.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
  done_copy.Transition.StateAfter  = D3D12_RESOURCE_STATE_GENERIC_READ;
  cmd_list->ResourceBarrier(1, &done_copy);
}
