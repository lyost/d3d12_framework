#include <sstream>
#include "private_inc/D3D12/Textures/D3D12_RenderTargetMSAA.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_CommandList.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2D.h"
#include "FrameworkException.h"
#include "private_inc/BuildSettings.h"
using namespace std;

RenderTargetMSAA* D3D12_RenderTargetMSAA::Create(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, RenderTargetViewFormat format)
{
  float clear_color[4] = { 0, 0, 0, 1 };
  return D3D12_RenderTargetMSAA::Create(graphics, width, height, sample_count, quality, format, clear_color);
}

RenderTargetMSAA* D3D12_RenderTargetMSAA::Create(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, RenderTargetViewFormat format, float clear_color[4])
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  D3D12_RenderTargetDescHeap* desc_heap = D3D12_RenderTargetDescHeap::Create(device, 1);

  D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle;
  desc_heap->GetNextDescriptor(cpu_handle, gpu_handle);

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(width, height, sample_count, quality, format, resource_desc);

  D3D12_HEAP_PROPERTIES heap_prop;
  heap_prop.Type                 = D3D12_HEAP_TYPE_DEFAULT;
  heap_prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  heap_prop.CreationNodeMask     = 0;
  heap_prop.VisibleNodeMask      = 0;

  D3D12_CLEAR_VALUE clear_value;
  clear_value.Format   = resource_desc.Format;
  clear_value.Color[0] = clear_color[0];
  clear_value.Color[1] = clear_color[1];
  clear_value.Color[2] = clear_color[2];
  clear_value.Color[3] = clear_color[3];

  ID3D12Resource* buffer;
  HRESULT rc = device->CreateCommittedResource(&heap_prop, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_RESOLVE_SOURCE, &clear_value, __uuidof(ID3D12Resource), (void**)&buffer);
  if (FAILED(rc))
  {
    throw FrameworkException("Unable to create buffer resource");
  }

  D3D12_RENDER_TARGET_VIEW_DESC view_desc;
  view_desc.Format               = (DXGI_FORMAT)format;
  view_desc.ViewDimension        = D3D12_RTV_DIMENSION_TEXTURE2DMS;
  view_desc.Texture2D.MipSlice   = 0;
  view_desc.Texture2D.PlaneSlice = 0;
  device->CreateRenderTargetView(buffer, &view_desc, cpu_handle);

  return new D3D12_RenderTargetMSAA(buffer, cpu_handle, desc_heap);
}

D3D12_RenderTargetMSAA::D3D12_RenderTargetMSAA(ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle, D3D12_RenderTargetDescHeap* desc_heap)
:m_render_target(target),
 m_rtv_handle(handle),
 m_desc_heap(desc_heap)
{
}

D3D12_RenderTargetMSAA::~D3D12_RenderTargetMSAA()
{
  m_render_target->Release();
  delete m_desc_heap;
}

ID3D12Resource* D3D12_RenderTargetMSAA::GetResource() const
{
  return m_render_target;
}

const D3D12_CPU_DESCRIPTOR_HANDLE& D3D12_RenderTargetMSAA::GetHandle() const
{
  return m_rtv_handle;
}

void D3D12_RenderTargetMSAA::PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2D& texture)
{
  ID3D12Device*              device      = ((D3D12_Core&)graphics).GetDevice();
  ID3D12Resource*            dst_texture = ((D3D12_Texture2D&)texture).GetBuffer();
  ID3D12GraphicsCommandList* cmd_list    = ((D3D12_CommandList&)command_list).GetCommandList();

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  D3D12_RESOURCE_DESC src_desc = m_render_target->GetDesc();
  D3D12_RESOURCE_DESC dst_desc = dst_texture->GetDesc();

  if (src_desc.Width != dst_desc.Width || src_desc.Height != dst_desc.Height || src_desc.DepthOrArraySize != dst_desc.DepthOrArraySize)
  {
    throw FrameworkException("Incompatible dimensions");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_RESOURCE_BARRIER prep_copy;
  prep_copy.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  prep_copy.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  prep_copy.Transition.pResource   = dst_texture;
  prep_copy.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  prep_copy.Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
  prep_copy.Transition.StateAfter  = D3D12_RESOURCE_STATE_COPY_DEST;
  cmd_list->ResourceBarrier(1, &prep_copy);

  cmd_list->CopyResource(dst_texture, m_render_target);

  D3D12_RESOURCE_BARRIER done_copy;
  done_copy.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  done_copy.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  done_copy.Transition.pResource   = dst_texture;
  done_copy.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  done_copy.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
  done_copy.Transition.StateAfter = D3D12_RESOURCE_STATE_GENERIC_READ;
  cmd_list->ResourceBarrier(1, &done_copy);
}

void D3D12_RenderTargetMSAA::GetResourceDesc(UINT width, UINT height, UINT sample_count, UINT quality, RenderTargetViewFormat format, D3D12_RESOURCE_DESC& resource_desc)
{
  resource_desc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  resource_desc.Alignment          = 0;
  resource_desc.Width              = width;
  resource_desc.Height             = height;
  resource_desc.DepthOrArraySize   = 1;
  resource_desc.MipLevels          = 1;
  resource_desc.Format             = (DXGI_FORMAT)format;
  resource_desc.SampleDesc.Count   = sample_count;
  resource_desc.SampleDesc.Quality = quality;
  resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;
  resource_desc.Flags              = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
}
