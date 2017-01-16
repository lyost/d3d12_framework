#ifndef RENDER_TARGET_MSAA_H
#define RENDER_TARGET_MSAA_H

class GraphicsCore;
class CommandList;
#include "Graphics/GraphicsCore.h"
#include "Graphics/RenderTargetViewFormats.h"
#include "Graphics/CommandList.h"

/// <summary>
/// Base class for a MSAA render target
/// </summary>
class RenderTargetMSAA
{
  public:
    /// <summary>
    /// Creates a D3D12 MSAA render target
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
    /// <param name="sample_count">
    /// number of multisamples per pixel
    /// </param>
    /// <param name="quality">
    /// image quality level
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
    static RenderTargetMSAA* CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, RenderTargetViewFormat format);

    /// <summary>
    /// Creates a D3D12 MSAA render target
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
    /// <param name="sample_count">
    /// number of multisamples per pixel
    /// </param>
    /// <param name="quality">
    /// image quality level
    /// </param>
    /// <param name="format">
    /// render target format
    /// </param>
    /// <param name="clear_color">
    /// RGBA default clear color
    /// </param>
    /// <returns>
    /// D3D12 render target
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static RenderTargetMSAA* CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, RenderTargetViewFormat format, float clear_color[4]);

    virtual ~RenderTargetMSAA();

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
    RenderTargetMSAA();
    
  private:
    // disabled
    RenderTargetMSAA(const RenderTargetMSAA& cpy);
    RenderTargetMSAA& operator=(const RenderTargetMSAA& cpy);
};

#endif /* RENDER_TARGET_MSAA_H */