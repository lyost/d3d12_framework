#ifndef D3D12_TEXTURE_3D_H
#define D3D12_TEXTURE_3D_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/Texture3D.h"

class D3D12_Texture3D : public Texture3D
{
  public:
    /// <summary>
    /// Creates a D3D12 texture
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="shader_buffer_heap">
    /// shader resources descriptor heap that the texture will be accessed from
    /// </param>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="height">
    /// height of the texture in pixels
    /// </param>
    /// <param name="depth">
    /// depth of the texture in pixels
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <param name="mip_levels">
    /// number of mipmap levels
    /// </param>
    /// <returns>
    /// D3D12 texture 3D
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture3D* Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 depth, GraphicsDataFormat format, UINT16 mip_levels);

    ~D3D12_Texture3D();

    /// <summary>
    /// Retrieves the D3D12 resource
    /// </summary>
    /// <returns>
    /// D3D12 resource for the texture
    /// </returns>
    ID3D12Resource* GetBuffer() const;

    /// <summary>
    /// Retrieves the GPU address for the texture
    /// </summary>
    /// <returns>
    /// GPU address for the texture
    /// </returns>
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUAddr() const;

    /// <summary>
    /// Retrieves the number of mipmap levels the resource was created with
    /// </summary>
    /// <returns>
    /// GPU address for the texture
    /// </returns>
    UINT16 GetNumMipmapLevels() const;

  private:
    // disabled
    D3D12_Texture3D();
    D3D12_Texture3D(const D3D12_Texture3D& cpy);
    D3D12_Texture3D& operator=(const D3D12_Texture3D& cpy);

    D3D12_Texture3D(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, UINT16 depth, GraphicsDataFormat format, UINT16 num_mip_levels);

    /// <summary>
    /// D3D12 texture resource
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// GPU address for the texture
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE m_gpu_mem;

    /// <summary>
    /// width of the texture in pixels
    /// </summary>
    UINT m_width;

    /// <summary>
    /// height of the texture in pixels
    /// </summary>
    UINT m_height;

    /// <summary>
    /// depth of the texture in pixels
    /// </summary>
    UINT16 m_depth;

    /// <summary>
    /// texture format
    /// </summary>
    GraphicsDataFormat m_format;

    /// <summary>
    /// number of mipmap levels in the resource
    /// </summary>
    UINT16 m_num_mipmap_levels;
};

#endif /* D3D12_TEXTURE_3D_H */
