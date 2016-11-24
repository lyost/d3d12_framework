#include "private_inc/D3D12/Textures/D3D12_DepthStencil.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/Textures/D3D12_DepthStencilResourceHeap.h"
#include "private_inc/D3D12/Buffers/D3D12_DepthStencilDescHeap.h"
#include "FrameworkException.h"

UINT D3D12_DepthStencil::GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height)
{
  const D3D12_Core& core = (const D3D12_Core&)graphics;
  ID3D12Device* device = core.GetDevice();

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(width, height, resource_desc);

  D3D12_RESOURCE_ALLOCATION_INFO alloc_info = device->GetResourceAllocationInfo(0, 1, &resource_desc);
  if (alloc_info.SizeInBytes > (UINT)alloc_info.SizeInBytes)
  {
    throw new FrameworkException("computed size is too large");
  }
  else
  {
    return (UINT)alloc_info.SizeInBytes;
  }
}

D3D12_DepthStencil* D3D12_DepthStencil::Create(const GraphicsCore& graphics, DepthStencilResourceHeap& resource_heap, DepthStencilDescHeap& depth_stencil_buffer_heap, UINT width, UINT height,
  float default_depth_clear)
{
  const D3D12_Core& core = (const D3D12_Core&)graphics;
  ID3D12Device* device = core.GetDevice();

  D3D12_DepthStencilDescHeap& desc_heap = (D3D12_DepthStencilDescHeap&)depth_stencil_buffer_heap;
  D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle;
  desc_heap.GetNextDescriptor(cpu_handle, gpu_handle);

  D3D12_DepthStencilResourceHeap& buffer_heap = (D3D12_DepthStencilResourceHeap&)resource_heap;

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(width, height, resource_desc);

  ID3D12Resource* buffer = buffer_heap.CreateResource(graphics, resource_desc, default_depth_clear);
  if (buffer == NULL)
  {
    throw new FrameworkException("Unable to create buffer resource");
  }

  D3D12_DEPTH_STENCIL_VIEW_DESC view_desc;
  view_desc.Format             = DXGI_FORMAT_D32_FLOAT;
  view_desc.ViewDimension      = D3D12_DSV_DIMENSION_TEXTURE2D;
  view_desc.Flags              = D3D12_DSV_FLAG_NONE;
  view_desc.Texture2D.MipSlice = 0;
  device->CreateDepthStencilView(buffer, &view_desc, cpu_handle);

  D3D12_RESOURCE_DESC res_desc = buffer->GetDesc();
  D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
  UINT64 upload_size = 0;
  device->GetCopyableFootprints(&res_desc, 0, 1, 0, &layout, NULL, NULL, &upload_size);
  upload_size += layout.Offset;

  return new D3D12_DepthStencil(buffer, gpu_handle, cpu_handle, width, height, upload_size);
}

D3D12_DepthStencil::D3D12_DepthStencil(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, D3D12_CPU_DESCRIPTOR_HANDLE cpu_mem, UINT width, UINT height, UINT64 upload_size)
:m_buffer(buffer),
 m_gpu_mem(gpu_mem),
 m_cpu_handle(cpu_mem),
 m_width(width),
 m_height(height),
 m_upload_size(upload_size)
{
}

D3D12_DepthStencil::~D3D12_DepthStencil()
{
  m_buffer->Release();
}

UINT64 D3D12_DepthStencil::GetUploadBufferSize() const
{
  return m_upload_size;
}

ID3D12Resource* D3D12_DepthStencil::GetBuffer() const
{
  return m_buffer;
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12_DepthStencil::GetGPUAddr() const
{
  return m_gpu_mem;
}

const D3D12_CPU_DESCRIPTOR_HANDLE& D3D12_DepthStencil::GetHandle() const
{
  return m_cpu_handle;
}

void D3D12_DepthStencil::GetResourceDesc(UINT width, UINT height, D3D12_RESOURCE_DESC& resource_desc)
{
  resource_desc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  resource_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  resource_desc.Width              = width;
  resource_desc.Height             = height;
  resource_desc.DepthOrArraySize   = 1;
  resource_desc.MipLevels          = 1;
  resource_desc.Format             = DXGI_FORMAT_D32_FLOAT;
  resource_desc.SampleDesc.Count   = 1;
  resource_desc.SampleDesc.Quality = 0;
  resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;
  resource_desc.Flags              = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL|D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
}
