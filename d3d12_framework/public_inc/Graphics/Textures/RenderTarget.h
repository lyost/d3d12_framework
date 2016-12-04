#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

class GraphicsCore;
class CommandList;
#include <vector>
#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"
#include "Graphics/CommandList.h"
#include "Graphics/Textures/Texture2D.h"

/// <summary>
/// Base class for a render target
/// </summary>
class RenderTarget
{
  public:
    /// <summary>
    /// Struct describing the configuration of a render target when creating them
    /// </summary>
    struct Config
    {
      /// <summary>
      /// width in pixels
      /// </summary>
      UINT width;

      /// <summary>
      /// height in pixels
      /// </summary>
      UINT height;

      /// <summary>
      /// render target format
      /// </summary>
      GraphicsDataFormat format;
    };

    /// <summary>
    /// Creates a render target from a 2D texture
    /// <summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="configs
    /// Configurations for render targets to create
    /// </param>
    /// <param name="out">
    /// Where to put the created depth stencils.  They will be added to the end of the array.
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static void CreateD3D12(const GraphicsCore& graphics, const std::vector<Config>& configs, std::vector<RenderTarget*>& out);

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