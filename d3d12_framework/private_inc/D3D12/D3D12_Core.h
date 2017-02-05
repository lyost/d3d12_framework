#ifndef D3D12_CORE_H
#define D3D12_CORE_H

#include <d3d12.h>
#include <dxgi1_4.h>
#include "Graphics/GraphicsCore.h"
#include "private_inc/D3D12/Buffers/D3D12_BackBuffer.h"

/// <summary>
/// Manages the core needed variables to use D3D12
/// </summary>
class D3D12_Core : public GraphicsCore
{
  public:
    /// <summary>
    /// Setups D3D12 for the specified window
    /// </summary>
    /// <param name="wnd">
    /// handle to the window to setup D3D12 for
    /// </param>
    /// <returns>
    /// pointer to the D3D12_Core instance for the window
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered in creating the instance
    /// </exception>
    static D3D12_Core* Create(HWND& wnd);
    
    /// <summary>
    /// Cleans up the D3D12 core.  All resources created with this D3D12 core
    /// instance must be cleaned up before calling this.
    /// </summary>
    ~D3D12_Core();
    
    /// <summary>
    /// Switches the graphics side of things from fullscreen to windowed and vice versa
    /// <summary>
    /// <param name="width">
    /// width of the client area, in pixels 
    /// </param>
    /// <param name="height">
    /// height of the client area, in pixels
    /// </param>
    /// <param name="enable">
    /// true  if the window should be fullscreen
    /// false if the window should be in windowed mode
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void Fullscreen(UINT width,UINT height,bool enable);
    
    /// <summary>
    /// Handles updating the D3D12 when the window is resized
    /// </summary>
    /// <param name="width">
    /// width of the new client area, in pixels 
    /// </param>
    /// <param name="height">
    /// height of the new client area, in pixels
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void OnResize(UINT width,UINT height);
    
    /// <summary>
    /// Waits for the fence for the default command queue to indicate that the command queue has finished
    /// </summary>
    void WaitOnFence();

    /// <summary>
    /// Performs the operations specified in the command list
    /// </summary>
    /// <param name="list">
    /// command list to execute
    /// </param>
    void ExecuteCommandList(const CommandList& list) const;

    /// <summary>
    /// Performs the operations specified in the command lists
    /// </summary>
    /// <param name="lists">
    /// bundle of command lists to execute
    /// </param>
    void ExecuteCommandLists(const CommandListBundle& lists) const;
    
    /// <summary>
    /// Swaps the back and front buffers to display the frame to the user
    /// </summary>
    void Swap();
    
    /// <summary>
    /// Retrieves a viewport specification that covers the entire window client
    /// area (which is automatically updated whenever the window is resized)
    /// </summary>
    /// <returns>
    /// viewport specification that covers the window's client area
    /// </returns>
    const Viewport& GetDefaultViewport() const;

    /// <summary>
    /// Retrieves the back buffers
    /// </summary>
    /// <returns>
    /// back buffers
    /// </returns>
    BackBuffers& GetBackBuffer() const;

    /// <summary>
    /// Retrieves information about support for multisampling with the requested parameters
    /// </summary>
    /// <param name="format">
    /// render target format
    /// </param>
    /// <param name="sample_count">
    /// number of multisamples per pixel
    /// </param>
    /// <param name="tiled">
    /// true if quality levels should be checked for tiled resources
    /// false otherwise
    /// </param>
    /// <returns>
    /// number of image quality levels
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    UINT CheckSupportedMultisampleLevels(GraphicsDataFormat format, UINT sample_count, bool tiled) const;

    /// <summary>
    /// Retrieves the D3D12 device
    /// </summary>
    /// <returns>
    /// D3D12 device
    /// </returns>
    ID3D12Device* GetDevice() const;
    
  private:
    D3D12_Core(ID3D12Device* device, ID3D12Fence* fence, HANDLE fence_event, IDXGISwapChain* swap_chain_base, IDXGISwapChain3* swap_chain, ID3D12CommandQueue* command_queue,
      D3D12_BackBuffers* back_buffer, const D3D12_VIEWPORT& viewport);
    
    // disabled
    D3D12_Core(const D3D12_Core& cpy);
    D3D12_Core& operator=(const D3D12_Core& cpy);
    
    /// <summary>
    /// D3D12 device
    /// </summary>
    ID3D12Device*           m_device;

    /// <summary>
    /// fence for waiting for the default command queue (m_command_queue) to finish
    /// </summary>
    ID3D12Fence*            m_fence;

    /// <summary>
    /// event when the fence is to be waited for
    /// </summary>
    HANDLE                  m_fence_event;

    /// <summary>
    /// next value the fence should wait for
    /// </summary>
    UINT64                  m_fence_value;

    /// <summary>
    /// swap chain that m_swap_chain is created from (needed only for cleanup)
    /// </summary>
    IDXGISwapChain*         m_swap_chain_base;
    
    /// <summary>
    /// swap chain
    /// </summary>
    IDXGISwapChain3*        m_swap_chain;

    /// <summary>
    /// command queue
    /// </summary>
    ID3D12CommandQueue*     m_command_queue;

    /// <summary>
    /// back buffers
    /// </summary>
    D3D12_BackBuffers*      m_back_buffer;
    
    /// <summary>
    /// viewport specification that covers the window's client area
    /// </summary>
    Viewport                m_default_viewport;

    /// <summary>
    /// keeps track if in full screen mode or not
    /// </summary>
    bool m_fullscreen;
};

#endif /* D3D12_CORE_H */
