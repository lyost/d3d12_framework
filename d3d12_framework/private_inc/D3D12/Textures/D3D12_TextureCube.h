#ifndef D3D12_TEXTURE_CUBE_H
#define D3D12_TEXTURE_CUBE_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/TextureCube.h"

class D3D12_TextureCube : public TextureCube
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
    /// width of a texture for each side of the cube in pixels
    /// </param>
    /// <param name="height">
    /// height of a texture for each side of the cube in pixels
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// D3D12 texture cube
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureCube* Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format);

    ~D3D12_TextureCube();

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

  private:
    // disabled
    D3D12_TextureCube();
    D3D12_TextureCube(const D3D12_TextureCube& cpy);
    D3D12_TextureCube& operator=(const D3D12_TextureCube& cpy);

    D3D12_TextureCube(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, GraphicsDataFormat format);

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
    /// texture format
    /// <summary>
    GraphicsDataFormat m_format;
};

#endif /* D3D12_TEXTURE_CUBE_H */
