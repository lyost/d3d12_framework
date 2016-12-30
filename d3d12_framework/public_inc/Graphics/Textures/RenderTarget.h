#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

class GraphicsCore;
class CommandList;
class Texture2DRenderTarget;
#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"
#include "Graphics/CommandList.h"
#include "Graphics/Textures/Texture2DRenderTarget.h"

/// <summary>
/// Base class for a render target
/// </summary>
class RenderTarget
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
    static RenderTarget* CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, GraphicsDataFormat format);

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
    static RenderTarget* CreateD3D12FromTexture(const GraphicsCore& graphics, const Texture2DRenderTarget& texture);

    virtual ~RenderTarget();

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
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2D& texture) = 0;
    
  protected:
    RenderTarget();
    
  private:
    // disabled
    RenderTarget(const RenderTarget& cpy);
    RenderTarget& operator=(const RenderTarget& cpy);
};

#endif /* RENDER_TARGET_H */