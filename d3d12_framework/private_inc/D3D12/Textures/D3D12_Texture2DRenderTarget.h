#ifndef D3D12_TEXTURE_2D_RENDER_TARGET_H
#define D3D12_TEXTURE_2D_RENDER_TARGET_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/Texture2DRenderTarget.h"

class D3D12_Texture2DRenderTarget : public Texture2DRenderTarget
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
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// D3D12 texture 2D
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture2DRenderTarget* Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format);

    ~D3D12_Texture2DRenderTarget();

    /// <summary>
    /// Retrieves the D3D12 resource
    /// </summary>
    /// <returns>
    /// D3D12 resource for the texture
    /// </returns>
    ID3D12Resource* GetResource() const;

    /// <summary>
    /// Retrieves the GPU address for the texture
    /// </summary>
    /// <returns>
    /// GPU address for the texture
    /// </returns>
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUAddr() const;

  private:
    // disabled
    D3D12_Texture2DRenderTarget();
    D3D12_Texture2DRenderTarget(const D3D12_Texture2DRenderTarget& cpy);
    D3D12_Texture2DRenderTarget& operator=(const D3D12_Texture2DRenderTarget& cpy);

    D3D12_Texture2DRenderTarget(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, GraphicsDataFormat format);

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
    /// <summary>
    UINT m_width;

    /// <summary>
    /// height of the texture in pixels
    /// <summary>
    UINT m_height;

    /// <summary>
    /// texture format
    /// <summary>
    GraphicsDataFormat m_format;
};

#endif /* D3D12_TEXTURE_2D_RENDER_TARGET_H */
