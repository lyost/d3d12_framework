#ifndef GRAPHICS_CORE_H
#define GRAPHICS_CORE_H

class CommandListBundle;
class BackBuffers;

#include <windows.h>
#include "Graphics/Viewport.h"
#include "Graphics/Buffers/BackBuffer.h"
#include "Graphics/CommandListBundle.h"

/// <summary>
/// Interface to core part of the graphics library used by implementations of this interface
/// </summary>
class GraphicsCore
{
  public:
    /// <summary>
    /// Setups D3D12 for the specified window
    /// </summary>
    /// <param name="wnd">
    /// handle to the window to setup D3D12 for
    /// </param>
    /// <returns>
    /// pointer to the GraphicsCore instance for the window
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered in creating the instance
    /// </exception>
    static GraphicsCore* CreateD3D12(HWND& wnd);
    
    /// <summary>
    /// Cleans up the GraphicsCore.  All resources created with this instance must be cleaned up before calling this.
    /// </summary>
    virtual ~GraphicsCore();

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
    virtual void Fullscreen(UINT width, UINT height, bool enable) = 0;

    /// <summary>
    /// Handles updating the GraphicsCore when the window is resized
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
    virtual void OnResize(UINT width, UINT height) = 0;
    
    /// <summary>
    /// Waits for the fence for the default command queue to indicate that the command queue has finished
    /// </summary>
    virtual void WaitOnFence() = 0;
    
    /// <summary>
    /// Swaps the back and front buffers to display the frame to the user
    /// </summary>
    virtual void Swap() = 0;

    /// <summary>
    /// Performs the operations specified in the command list
    /// </summary>
    /// <param name="list">
    /// command list to execute
    /// </param>
    virtual void ExecuteCommandList(const CommandList& list) const = 0;

    /// <summary>
    /// Performs the operations specified in the command lists
    /// </summary>
    /// <param name="lists">
    /// bundle of command lists to execute
    /// </param>
    virtual void ExecuteCommandLists(const CommandListBundle& lists) const = 0;

    /// <summary>
    /// Retrieves a viewport specification that covers the entire window client area (which is automatically updated whenever the window is resized)
    /// </summary>
    /// <returns>
    /// viewport specification that covers the window's client area
    /// </returns>
    virtual const Viewport& GetDefaultViewport() const = 0;

    /// <summary>
    /// Retrieves the back buffers
    /// </summary>
    /// <returns>
    /// back buffers
    /// </returns>
    virtual BackBuffers& GetBackBuffer() const = 0;

    /// <summary>
    /// Retrieves information about support for multisampling with the requested parameters
    /// </summary>
    /// <param name="format">
    /// todo
    /// </param>
    /// <param name="sample_count">
    /// todo
    /// </param>
    /// <param name="tiled">
    /// todo
    /// </param>
    /// <param name="num_quality_levels">
    /// todo
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void CheckSupportedMultisampleLevels(GraphicsDataFormat& format, UINT& sample_count, bool& tiled, UINT& num_quality_levels) const = 0;

  protected:
    GraphicsCore();
    
  private:
    // disabled
    GraphicsCore(const GraphicsCore& cpy);
    GraphicsCore& operator=(const GraphicsCore& cpy);
};

#endif /* GRAPHICS_CORE_H */
