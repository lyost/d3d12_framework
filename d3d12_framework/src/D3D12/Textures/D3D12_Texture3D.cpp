#include "private_inc/D3D12/Textures/D3D12_Texture3D.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/Textures/D3D12_TextureResourceHeap.h"
#include "private_inc/D3D12/D3D12_ShaderResourceDescHeap.h"
#include "FrameworkException.h"

UINT D3D12_Texture3D::GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height, UINT16 depth, GraphicsDataFormat format)
{
  const D3D12_Core& core = (const D3D12_Core&)graphics;
  ID3D12Device* device = core.GetDevice();

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(width, height, depth, format, resource_desc);

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

Texture3D* D3D12_Texture3D::Create(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 depth,
  GraphicsDataFormat format)
{
  const D3D12_Core& core = (const D3D12_Core&)graphics;
  ID3D12Device* device = core.GetDevice();

  D3D12_ShaderResourceDescHeap& desc_heap = (D3D12_ShaderResourceDescHeap&)shader_buffer_heap;
  D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle;
  desc_heap.GetNextDescriptor(cpu_handle, gpu_handle);

  D3D12_TextureResourceHeap& buffer_heap = (D3D12_TextureResourceHeap&)resource_heap;

  D3D12_RESOURCE_DESC resource_desc;
  GetResourceDesc(width, height, depth, format, resource_desc);

  ID3D12Resource* buffer = buffer_heap.CreateResource(graphics, resource_desc);
  if (buffer == NULL)
  {
    throw FrameworkException("Unable to create buffer resource");
  }

  D3D12_SHADER_RESOURCE_VIEW_DESC src_desc;
  src_desc.Format                        = (DXGI_FORMAT)format;
  src_desc.ViewDimension                 = D3D12_SRV_DIMENSION_TEXTURE3D;
  src_desc.Shader4ComponentMapping       = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  src_desc.Texture3D.MostDetailedMip     = 0;
  src_desc.Texture3D.MipLevels           = 1;
  src_desc.Texture3D.ResourceMinLODClamp = 0;
  device->CreateShaderResourceView(buffer, &src_desc, cpu_handle);

  D3D12_RESOURCE_DESC res_desc = buffer->GetDesc();
  D3D12_PLACED_SUBRESOURCE_FOOTPRINT layout;
  UINT64 upload_size = 0;
  device->GetCopyableFootprints(&res_desc, 0, 1, 0, &layout, NULL, NULL, &upload_size);
  upload_size += layout.Offset;

  return new D3D12_Texture3D(buffer, gpu_handle, width, height, depth, format, upload_size);
}

D3D12_Texture3D::D3D12_Texture3D(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, UINT16 depth, GraphicsDataFormat format, UINT64 upload_size)
:m_buffer(buffer),
 m_gpu_mem(gpu_mem),
 m_width(width),
 m_height(height),
 m_depth(depth),
 m_format(format),
 m_upload_size(upload_size)
{
}

D3D12_Texture3D::~D3D12_Texture3D()
{
  m_buffer->Release();
}

UINT64 D3D12_Texture3D::GetUploadBufferSize() const
{
  return m_upload_size;
}

ID3D12Resource* D3D12_Texture3D::GetBuffer() const
{
  return m_buffer;
}

D3D12_GPU_DESCRIPTOR_HANDLE D3D12_Texture3D::GetGPUAddr() const
{
  return m_gpu_mem;
}

void D3D12_Texture3D::GetResourceDesc(UINT width, UINT height, UINT16 depth, GraphicsDataFormat format, D3D12_RESOURCE_DESC& resource_desc)
{
  resource_desc.Dimension          = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
  resource_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  resource_desc.Width              = width;
  resource_desc.Height             = height;
  resource_desc.DepthOrArraySize   = depth;
  resource_desc.MipLevels          = 1;
  resource_desc.Format             = (DXGI_FORMAT)format;
  resource_desc.SampleDesc.Count   = 1;
  resource_desc.SampleDesc.Quality = 0;
  resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;
  resource_desc.Flags              = D3D12_RESOURCE_FLAG_NONE;
}
