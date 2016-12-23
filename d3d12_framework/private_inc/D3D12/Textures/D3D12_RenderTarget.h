#ifndef D3D12_RENDER_TARGET_H
#define D3D12_RENDER_TARGET_H

#include <d3d12.h>
#include "Graphics/Textures/RenderTarget.h"

/// <summary>
/// Wrapper for a D3D12 render target
/// </summary>
class D3D12_RenderTarget : public RenderTarget
{
  public:
    /// <summary>
    /// Creates render targets for the specified configurations
    /// <summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="configs">
    /// Configurations for render targets to create
    /// </param>
    /// <param name="out">
    /// Where to put the created render targets.  They will be added to the end of the array.
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static void Create(const GraphicsCore& graphics, const std::vector<Config>& configs, std::vector<RenderTarget*>& out);

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
    D3D12_RenderTarget(ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle, ID3D12DescriptorHeap* desc_heap);

    // disabled
    D3D12_RenderTarget();
    D3D12_RenderTarget(const D3D12_RenderTarget& cpy);
    D3D12_RenderTarget& operator=(const D3D12_RenderTarget& cpy);

    /// <summary>
    /// Determines the size render target will need to be to hold the requested number of bytes
    /// </summary>
    /// <param name="device">
    /// d3d12 device
    /// </param>
    /// <param name="config">
    /// configuration to use for the render target
    /// </param>
    /// <returns>
    /// number of bytes the render target should be created with
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static UINT GetAlignedSize(ID3D12Device* device, const Config& config);

    /// <summary>
    /// Helper function to fill in a D3D12 resource description struct
    /// </summary>
    /// <param name="config">
    /// configuration to use for the render target
    /// </param>
    /// <param name="resource_desc">
    /// output paramenter of the resource description struct to fill in
    /// </param>
    static void GetResourceDesc(const Config& config, D3D12_RESOURCE_DESC& resource_desc);

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
    ID3D12DescriptorHeap* m_desc_heap;
};

#endif /* D3D12_RENDER_TARGET_H */