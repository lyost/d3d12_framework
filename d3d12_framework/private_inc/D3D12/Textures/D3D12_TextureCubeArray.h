#ifndef D3D12_TEXTURE_CUBE_ARRAY_H
#define D3D12_TEXTURE_CUBE_ARRAY_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/TextureCubeArray.h"

class D3D12_TextureCubeArray : public TextureCubeArray
{
  public:
    /// <summary>
    /// Creates a D3D12 texture cube array
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="shader_buffer_heap">
    /// shader resources descriptor heap that the texture will be accessed from
    /// </param>
    /// <param name="width">
    /// width of a texture for each side of the cube in pixels
    /// </param>
    /// <param name="height">
    /// height of a texture for each side of the cube in pixels
    /// </param>
    /// <param name="num_cubes">
    /// number of cubes in the array
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <param name="mip_levels">
    /// number of mipmap levels
    /// </param>
    /// <returns>
    /// D3D12 texture cube array
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureCubeArray* Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 num_cubes, GraphicsDataFormat format, UINT16 mip_levels);

    ~D3D12_TextureCubeArray();

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
    D3D12_TextureCubeArray();
    D3D12_TextureCubeArray(const D3D12_TextureCubeArray& cpy);
    D3D12_TextureCubeArray& operator=(const D3D12_TextureCubeArray& cpy);

    D3D12_TextureCubeArray(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, UINT16 num_sides, GraphicsDataFormat format, UINT16 num_mip_levels);

    /// <summary>
    /// D3D12 texture resource
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// GPU address for the texture
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE m_gpu_mem;

    /// <summary>
    /// width of a texture for each side of the cube in pixels
    /// <summary>
    UINT m_width;

    /// <summary>
    /// height of a texture for each side of the cube in pixels
    /// <summary>
    UINT m_height;

    /// <summary>
    /// length of the texture array in terms of the number of sides, not number of cubes
    /// <summary>
    UINT16 m_length;

    /// <summary>
    /// texture format
    /// <summary>
    GraphicsDataFormat m_format;

    /// <summary>
    /// number of mipmap levels in the resource
    /// </summary>
    UINT16 m_num_mipmap_levels;
};

#endif /* D3D12_TEXTURE_CUBE_ARRAY_H */
