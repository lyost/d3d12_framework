#include "private_inc/D3D12/Textures/D3D12_RenderTarget.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_CommandList.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2D.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTargetResourceHeap.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTargetDescHeap.h"
#include "FrameworkException.h"
#include "private_inc/BuildSettings.h"
using namespace std;

void D3D12_RenderTarget::Create(const GraphicsCore& graphics, const vector<Config>& configs, vector<RenderTarget*>& out)
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  UINT64 total_heap_bytes = 0;
  vector<Config>::const_iterator config_it = configs.begin();
  while (config_it != configs.end())
  {
    total_heap_bytes += GetAlignedSize(device, *config_it);

    ++config_it;
  }

  D3D12_RenderTargetResourceHeap* resource_heap = D3D12_RenderTargetResourceHeap::Create(device, total_heap_bytes);
  D3D12_RenderTargetDescHeap*     desc_heap     = D3D12_RenderTargetDescHeap::Create(device, configs.size());

  config_it = configs.begin();
  while (config_it != configs.end())
  {
    D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle;
    D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle;
    desc_heap->GetNextDescriptor(cpu_handle, gpu_handle);

    D3D12_RESOURCE_DESC resource_desc;
    GetResourceDesc(*config_it, resource_desc);

    ID3D12Resource* buffer = resource_heap->CreateResource(device, resource_desc);
    if (buffer == NULL)
    {
      throw FrameworkException("Unable to create render target resource");
    }

    D3D12_RENDER_TARGET_VIEW_DESC view_desc;
    view_desc.Format               = (DXGI_FORMAT)config_it->format;
    view_desc.ViewDimension        = D3D12_RTV_DIMENSION_TEXTURE2D;
    view_desc.Texture2D.MipSlice   = 0;
    view_desc.Texture2D.PlaneSlice = 0;
    device->CreateRenderTargetView(buffer, &view_desc, cpu_handle);

    out.push_back(new D3D12_RenderTarget(buffer, cpu_handle, desc_heap->GetHeap()));

    ++config_it;
  }

  delete desc_heap;
  delete resource_heap;
}

D3D12_RenderTarget::D3D12_RenderTarget(ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle)
  :m_render_target(target),
  m_rtv_handle(handle),
  m_desc_heap(NULL)
{
  m_render_target->AddRef();
}

D3D12_RenderTarget::D3D12_RenderTarget(ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle, ID3D12DescriptorHeap* desc_heap)
:m_render_target(target),
 m_rtv_handle(handle),
 m_desc_heap(desc_heap)
{
  m_desc_heap->AddRef();
}

D3D12_RenderTarget::~D3D12_RenderTarget()
{
  m_render_target->Release();
  if (m_desc_heap)
  {
    m_desc_heap->Release();
  }
}

ID3D12Resource* D3D12_RenderTarget::GetResource() const
{
  return m_render_target;
}

const D3D12_CPU_DESCRIPTOR_HANDLE& D3D12_RenderTarget::GetHandle() const
{
  return m_rtv_handle;
}

void D3D12_RenderTarget::PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture& texture)
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
  prep_copy.Transition.StateBefore = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
  prep_copy.Transition.StateAfter  = D3D12_RESOURCE_STATE_COPY_DEST;
  cmd_list->ResourceBarrier(1, &prep_copy);

  cmd_list->CopyResource(dst_texture, m_render_target);

  D3D12_RESOURCE_BARRIER done_copy;
  done_copy.Type  = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  done_copy.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  done_copy.Transition.pResource   = dst_texture;
  done_copy.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  done_copy.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
  done_copy.Transition.StateAfter = D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE;
  cmd_list->ResourceBarrier(1, &done_copy);
}

UINT D3D12_RenderTarget::GetAlignedSize(ID3D12Device* device, const Config& config)
{
  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(config, resource_desc);

  D3D12_RESOURCE_ALLOCATION_INFO alloc_info = device->GetResourceAllocationInfo(0, 1, &resource_desc);
  if (alloc_info.SizeInBytes > (UINT)alloc_info.SizeInBytes)
  {
    throw FrameworkException("computed size is too large");
  }
  else
  {
    return (UINT)alloc_info.SizeInBytes;
  }
}

void D3D12_RenderTarget::GetResourceDesc(const Config& config, D3D12_RESOURCE_DESC& resource_desc)
{
  resource_desc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  resource_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  resource_desc.Width              = config.width;
  resource_desc.Height             = config.height;
  resource_desc.DepthOrArraySize   = 1;
  resource_desc.MipLevels          = 1;
  resource_desc.Format             = (DXGI_FORMAT)config.format;
  resource_desc.SampleDesc.Count   = 1;
  resource_desc.SampleDesc.Quality = 0;
  resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;
  resource_desc.Flags              = D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET;
}
