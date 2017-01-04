#include "private_inc/D3D12/Textures/D3D12_Texture.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_ShaderResourceDescHeap.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

D3D12_Texture::CreatedTexture D3D12_Texture::Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 depth, GraphicsDataFormat format,
  D3D12_SRV_DIMENSION dimension, D3D12_RESOURCE_FLAGS flags, UINT16 mip_levels)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (mip_levels == 0)
  {
    // D3D12 allows for the D3D12_RESOURCE_DESC to have a MipLevels of 0 (https://msdn.microsoft.com/en-us/library/windows/desktop/dn903813%28v=vs.85%29.aspx), but the framework's
    // D3D12_TextureUploadBuffer relies on a non-zero number of mipmap levels to determine the subresource index
    throw FrameworkException("The number of mipmap levels cannot be 0");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_Core& core = (const D3D12_Core&)graphics;
  ID3D12Device* device = core.GetDevice();

  D3D12_ShaderResourceDescHeap& desc_heap = (D3D12_ShaderResourceDescHeap&)shader_buffer_heap;
  D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle;
  D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle;
  desc_heap.GetNextDescriptor(cpu_handle, gpu_handle);

  D3D12_RESOURCE_DESC resource_desc;
  if (dimension == D3D12_SRV_DIMENSION_TEXTURE1D || dimension == D3D12_SRV_DIMENSION_TEXTURE1DARRAY)
  {
    resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE1D;
  }
  else if (dimension == D3D12_SRV_DIMENSION_TEXTURE2D || dimension == D3D12_SRV_DIMENSION_TEXTURE2DARRAY
    || dimension == D3D12_SRV_DIMENSION_TEXTURECUBE || dimension == D3D12_SRV_DIMENSION_TEXTURECUBEARRAY)
  {
    resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
  }
  else if (dimension == D3D12_SRV_DIMENSION_TEXTURE3D)
  {
    resource_desc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE3D;
  }
  else
  {
    throw FrameworkException("Unsupported texture type");
  }
  resource_desc.Alignment          = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
  resource_desc.Width              = width;
  resource_desc.Height             = height;
  resource_desc.DepthOrArraySize   = depth;
  resource_desc.MipLevels          = mip_levels;
  resource_desc.Format             = (DXGI_FORMAT)format;
  resource_desc.SampleDesc.Count   = 1;
  resource_desc.SampleDesc.Quality = 0;
  resource_desc.Layout             = D3D12_TEXTURE_LAYOUT_UNKNOWN;
  resource_desc.Flags              = flags;

  D3D12_HEAP_PROPERTIES heap_prop;
  heap_prop.Type                 = D3D12_HEAP_TYPE_DEFAULT;
  heap_prop.CPUPageProperty      = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
  heap_prop.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
  heap_prop.CreationNodeMask     = 0;
  heap_prop.VisibleNodeMask      = 0;

  D3D12_CLEAR_VALUE* clear_value = NULL;
  if (flags & D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET)
  {
    clear_value = new D3D12_CLEAR_VALUE;
    clear_value->Format   = resource_desc.Format;
    clear_value->Color[0] = 0;
    clear_value->Color[1] = 0;
    clear_value->Color[2] = 0;
    clear_value->Color[3] = 1;
  }

  ID3D12Resource* buffer;
  HRESULT rc = device->CreateCommittedResource(&heap_prop, D3D12_HEAP_FLAG_NONE, &resource_desc, D3D12_RESOURCE_STATE_GENERIC_READ, clear_value, __uuidof(ID3D12Resource), (void**)&buffer);
  delete clear_value;
  if (FAILED(rc))
  {
    throw FrameworkException("Unable to create buffer resource");
  }

  D3D12_SHADER_RESOURCE_VIEW_DESC src_desc;
  src_desc.Format                        = (DXGI_FORMAT)format;
  src_desc.ViewDimension                 = dimension;
  src_desc.Shader4ComponentMapping       = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
  if (dimension == D3D12_SRV_DIMENSION_TEXTURE1D)
  {
    src_desc.Texture1D.MostDetailedMip     = 0;
    src_desc.Texture1D.MipLevels           = mip_levels;
    src_desc.Texture1D.ResourceMinLODClamp = 0;
  }
  else if (dimension == D3D12_SRV_DIMENSION_TEXTURE1DARRAY)
  {
    src_desc.Texture1DArray.MostDetailedMip     = 0;
    src_desc.Texture1DArray.MipLevels           = mip_levels;
    src_desc.Texture1DArray.FirstArraySlice     = 0;
    src_desc.Texture1DArray.ArraySize           = depth;
    src_desc.Texture1DArray.ResourceMinLODClamp = 0;
  }
  else if (dimension == D3D12_SRV_DIMENSION_TEXTURE2D)
  {
    src_desc.Texture2D.MostDetailedMip     = 0;
    src_desc.Texture2D.MipLevels           = mip_levels;
    src_desc.Texture2D.PlaneSlice          = 0;
    src_desc.Texture2D.ResourceMinLODClamp = 0;

  }
  else if (dimension == D3D12_SRV_DIMENSION_TEXTURE2DARRAY)
  {
    src_desc.Texture2DArray.MostDetailedMip     = 0;
    src_desc.Texture2DArray.MipLevels           = mip_levels;
    src_desc.Texture2DArray.FirstArraySlice     = 0;
    src_desc.Texture2DArray.ArraySize           = depth;
    src_desc.Texture2DArray.PlaneSlice          = 0;
    src_desc.Texture2DArray.ResourceMinLODClamp = 0;
  }
  else if (dimension == D3D12_SRV_DIMENSION_TEXTURE3D)
  {
    src_desc.Texture3D.MostDetailedMip     = 0;
    src_desc.Texture3D.MipLevels           = mip_levels;
    src_desc.Texture3D.ResourceMinLODClamp = 0;
  }
  else if (dimension == D3D12_SRV_DIMENSION_TEXTURECUBE)
  {
    src_desc.TextureCube.MostDetailedMip     = 0;
    src_desc.TextureCube.MipLevels           = mip_levels;
    src_desc.TextureCube.ResourceMinLODClamp = 0;
  }
  else if (dimension == D3D12_SRV_DIMENSION_TEXTURECUBEARRAY)
  {
    src_desc.TextureCubeArray.MostDetailedMip     = 0;
    src_desc.TextureCubeArray.MipLevels           = mip_levels;
    src_desc.TextureCubeArray.First2DArrayFace    = 0;
    src_desc.TextureCubeArray.NumCubes            = depth / 6;
    src_desc.TextureCubeArray.ResourceMinLODClamp = 0;
  }
  device->CreateShaderResourceView(buffer, &src_desc, cpu_handle);

  return { buffer, gpu_handle };
}
