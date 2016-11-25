#ifndef DEPTH_STENCIL_H
#define DEPTH_STENCIL_H

#include <vector>
#include "Graphics/GraphicsCore.h"

class DepthStencil
{
  public:
    /// <summary>
    /// Struct describing the configuration of a depth stencil when creating them
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
      /// default value to use for clearing the depth stencil
      /// </summary>
      float default_depth_clear;
    };

    /// <summary>
    /// Creates D3D12 depth stencils for each entry in configs placed into out in the same order as entries in the configs array
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="configs">
    /// Configurations for depth stencils to create
    /// </param>
    /// <param name="out">
    /// Where to put the created depth stencils.  They will be added to the end of the array.
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static void CreateD3D12(const GraphicsCore& graphics, const std::vector<Config>& configs, std::vector<DepthStencil*>& out);

    virtual ~DepthStencil();

    /// <summary>
    /// Retrieves the required size for a depth stencil upload buffer that matches this depth stencil
    /// </summary>
    /// <returns>
    /// required number of bytes in the upload buffer
    /// </returns>
    virtual UINT64 GetUploadBufferSize() const = 0;
    
  protected:
    DepthStencil();

  private:
    // disabled
    DepthStencil(const DepthStencil& cpy);
    DepthStencil& operator=(const DepthStencil& cpy);
};

#endif /* DEPTH_STENCIL_H */
