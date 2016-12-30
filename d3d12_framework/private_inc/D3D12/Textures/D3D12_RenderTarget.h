#ifndef D3D12_RENDER_TARGET_H
#define D3D12_RENDER_TARGET_H

#include <d3d12.h>
#include "Graphics/Textures/RenderTarget.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTargetDescHeap.h"

/// <summary>
/// Wrapper for a D3D12 render target
/// </summary>
class D3D12_RenderTarget : public RenderTarget
{
  public:
    /// <summary>
    /// Creates a D3D12 render target
    /// <summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="width">
    /// width in pixels
    /// </param>
    /// <param name="height">
    /// height in pixels
    /// </param>
    /// <param name="format">
    /// render target format
    /// </param>
    /// <returns>
    /// D3D12 render target
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static RenderTarget* Create(const GraphicsCore& graphics, UINT width, UINT height, GraphicsDataFormat format);

    /// <summary>
    /// Creates a D3D12 render target using the same resource as the specified texture
    /// <summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="texture">
    /// texture create a render target view for
    /// </param>
    /// <returns>
    /// D3D12 render target
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static RenderTarget* CreateFromTexture(const GraphicsCore& graphics, const Texture2DRenderTarget& texture);

    D3D12_RenderTarget(ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle);
    ~D3D12_RenderTarget();

    /// <summary>
    /// Retrieves the D3D12 resource of the render target
    /// </summary>
    /// <returns>
    /// D3D12 resource for the texture
    /// </returns>
    ID3D12Resource* GetResource() const;

    /// <summary>
    /// Retrieves the D3D12 CPU descriptor handle for the render target
    /// </summary>
    /// <returns>
    /// D3D12 CPU descriptor handle
    /// </returns>
    const D3D12_CPU_DESCRIPTOR_HANDLE& GetHandle() const;

    /// <summary>
    /// Preps the command list for uploading the render target's data to the specified texture.  The command list must execute followed by a fence for the transfer to be completed.
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="command_list">
    /// command list to use for uploading
    /// </param>
    /// <param name="texture">
    /// texture to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2D& texture);
    
  private:
    D3D12_RenderTarget(ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle, D3D12_RenderTargetDescHeap* desc_heap);

    // disabled
    D3D12_RenderTarget();
    D3D12_RenderTarget(const D3D12_RenderTarget& cpy);
    D3D12_RenderTarget& operator=(const D3D12_RenderTarget& cpy);

    /// <summary>
    /// Helper function to fill in a D3D12 resource description struct
    /// </summary>
    /// <param name="width">
    /// width in pixels
    /// </param>
    /// <param name="height">
    /// height in pixels
    /// </param>
    /// <param name="format">
    /// render target format
    /// </param>
    /// <param name="resource_desc">
    /// output paramenter of the resource description struct to fill in
    /// </param>
    static void GetResourceDesc(UINT width, UINT height, GraphicsDataFormat format, D3D12_RESOURCE_DESC& resource_desc);

    /// <summary>
    /// render target
    /// </summary>
    ID3D12Resource* m_render_target;

    /// <summary>
    /// CPU descriptor handle for render target
    /// </summary>
    D3D12_CPU_DESCRIPTOR_HANDLE m_rtv_handle;

    /// <summary>
    /// D3D12 descriptor heap that the render target was created from
    /// </summary>
    D3D12_RenderTargetDescHeap* m_desc_heap;
};

#endif /* D3D12_RENDER_TARGET_H */