#ifndef D3D12_BACK_BUFFER_H
#define D3D12_BACK_BUFFER_H

#include <d3d12.h>
#include <dxgi1_4.h>
#include "Graphics/Buffers/BackBuffer.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTarget.h"

/// <summary>
/// Manages the back buffers
/// </summary>
/// <remarks>
/// Unlike other most other classes in this library, the user of this library does not create instances of this class.  The appropriate GraphicsCore subclass creates and manages the lifetime of instances
/// of this class.
/// </remarks>
class D3D12_BackBuffers : public BackBuffers
{
  public:
    /// <summary>
    /// Creates a back buffer with two render targets for the specified device and swap chain
    /// </summary>
    /// <param name="device">
    /// D3D12 device to create the back buffer for
    /// </param>
    /// <param name="swap_chain">
    /// swap chain to create the back buffer for
    /// </param>
    /// <returns>
    /// pointer to the D3D12_BackBuffers instance
    // </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static D3D12_BackBuffers* Create(ID3D12Device* device, IDXGISwapChain3* swap_chain);

    ~D3D12_BackBuffers();
    
    /// <summary>
    /// Updates which render target will be rendered to next
    /// </summary>
    void UpdateCurrentRenderTarget();

    /// <summary>
    /// Retrieves the current render target
    /// </summary>
    const RenderTarget& GetCurrentRenderTarget() const;
    
  private:
    // disabled
    D3D12_BackBuffers();
    D3D12_BackBuffers(const D3D12_BackBuffers& cpy);
    D3D12_BackBuffers& operator=(const D3D12_BackBuffers& cpy);

    /// <summary>
    /// Creates a back buffer that supports the specified number of render targets
    /// </summary>
    /// <param name="num">
    /// number of render targets to support as part of the back buffer
    /// </param>
    /// <param name="swap_chain">
    /// swap chain to use for UpdateCurrentRenderTarget
    /// </param>
    D3D12_BackBuffers(UINT num, ID3D12DescriptorHeap* render_target_view, IDXGISwapChain3* swap_chain);

    /// <summary>
    /// Adds a render target to the list of ones that are part of the back buffer
    /// </summary>
    /// <param name="index">
    /// index of the render target in the back buffer
    /// </param>
    /// <param name="target">
    /// D3D12 resource for the render target to add to the back buffer
    /// </param>
    /// <param name="handle">
    /// D3D12 CPU descriptor handle for target
    /// </param>
    void AddRenderTarget(UINT index, ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle);

    /// <summary>
    /// array length of m_targets
    /// </summary>
    UINT m_num;

    /// <summary>
    /// array of the render targets
    /// </summary>
    const D3D12_RenderTarget** m_targets;

    /// <summary>
    /// render target heap that the back buffers are from
    /// </summary>
    ID3D12DescriptorHeap* m_render_target_heap;

    /// <summary>
    /// index of current render target for the back buffer
    /// </summary>
    UINT m_curr_render_target;

    /// <summary>
    /// index of current render target for the back buffer
    /// </summary>
    IDXGISwapChain3* m_swap_chain;
};

#endif /* D3D12_BACK_BUFFER_H */