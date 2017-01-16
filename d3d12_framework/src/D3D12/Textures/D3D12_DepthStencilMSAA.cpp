#include <sstream>
#include "private_inc/D3D12/Textures/D3D12_DepthStencilMSAA.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "FrameworkException.h"
#include "private_inc/BuildSettings.h"
using namespace std;

DepthStencilMSAA* D3D12_DepthStencilMSAA::Create(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, float default_depth_clear)
{
  const D3D12_Core& core   = (const D3D12_Core&)graphics;
  ID3D12Device*     device = core.GetDevice();

  D3D12_DepthStencilDescHeap* desc_heap = D3D12_DepthStencilDescHeap::Create(device, 1);

  D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle;
  desc_heap->GetNextDescriptor(cpu_handle, gpu_handle);

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(width, height, sample_count, quality, resource_desc);
  D3D12_HEAP_PROPERTIES heap_prop;
  heap_prop.Type                 = D3D12_HEAP_TYPE_DEFAULT;
  heap_prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  heap_prop.CreationNodeMask     = 0;
  heap_prop.VisibleNodeMask      = 0;

  D3D12_CLEAR_VALUE clear;
  clear.Format               = DXGI_FORMAT_D32_FLOAT;
  clear.DepthStencil.Depth   = default_depth_clear;
  clear.DepthStencil.Stencil = 0;

  ID3D12Resource* buffer;
  HRESULT rc = device->CreateCommittedResource(&heap_prop, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_DEPTH_WRITE, &clear, __uuidof(ID3D12Resource), (void**)&buffer);
  if (FAILED(rc))
  {
    throw FrameworkException("Unable to create buffer resource");
  }

  D3D12_DEPTH_STENCIL_VIEW_DESC view_desc;
  view_desc.Format             = DXGI_FORMAT_D32_FLOAT;
  view_desc.ViewDimension      = D3D12_DSV_DIMENSION_TEXTURE2DMS;
  view_desc.Flags              = D3D12_DSV_FLAG_NONE;
  view_desc.Texture2D.MipSlice = 0;
  device->CreateDepthStencilView(buffer, &view_desc, cpu_handle);

  D3D12_RESOURCE_DESC res_desc = buffer->GetDesc();
  D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
  UINT64 upload_size = 0;
  device->GetCopyableFootprints(&res_desc, 0, 1, 0, &layout, NULL, NULL, &upload_size);
  upload_size += layout.Offset;

  return new D3D12_DepthStencilMSAA(buffer, gpu_handle, cpu_handle, width, height, upload_size, desc_heap);
}

D3D12_DepthStencilMSAA::D3D12_DepthStencilMSAA(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, D3D12_CPU_DESCRIPTOR_HANDLE cpu_mem, UINT width, UINT height, UINT64 upload_size,
  D3D12_DepthStencilDescHeap* desc_heap)
:m_buffer(buffer),
 m_gpu_mem(gpu_mem),
 m_cpu_handle(cpu_mem),
 m_width(width),
 m_height(height),
 m_desc_heap(desc_heap)
{
}

D3D12_DepthStencilMSAA::~D3D12_DepthStencilMSAA()
{
  m_buffer->Release();
  delete m_desc_heap;
}

ID3D12Resource* D3D12_DepthStencilMSAA::GetBuffer() const
{
  return m_buffer;
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12_DepthStencilMSAA::GetGPUAddr() const
{
  return m_gpu_mem;
}

const D3D12_CPU_DESCRIPTOR_HANDLE& D3D12_DepthStencilMSAA::GetHandle() const
{
  return m_cpu_handle;
}

void D3D12_DepthStencilMSAA::GetResourceDesc(UINT width, UINT height, UINT sample_count, UINT quality, D3D12_RESOURCE_DESC& resource_desc)
{
  resource_desc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  resource_desc.Alignment          = 0;
  resource_desc.Width              = width;
  resource_desc.Height             = height;
  resource_desc.DepthOrArraySize   = 1;
  resource_desc.MipLevels          = 1;
  resource_desc.Format             = DXGI_FORMAT_D32_FLOAT;
  resource_desc.SampleDesc.Count   = sample_count;
  resource_desc.SampleDesc.Quality = quality;
  resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;
  resource_desc.Flags              = D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL|D3D12_RESOURCE_FLAG_DENY_SHADER_RESOURCE;
}
