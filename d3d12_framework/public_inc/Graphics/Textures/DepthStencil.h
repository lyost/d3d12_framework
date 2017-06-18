#ifndef DEPTH_STENCIL_H
#define DEPTH_STENCIL_H

#include "Graphics/GraphicsCore.h"

class DepthStencil
{
  public:
    /// <summary>
    /// Creates a D3D12 depth stencil
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="width">
    /// width in pixels
    /// </param>
    /// <param name="height">
    /// height in pixels
    /// </param>
    /// <param name="default_depth_clear">
    /// default value to use for clearing the depth stencil
    /// </param>
    /// <param name="with_stencil">
    /// true  if the a byte per pixel for the stencil should be part of the buffer
    /// false if the buffer should be just depth data
    /// </param>
    /// <returns>
    /// D3D12 depth stencil
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static DepthStencil* CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, float default_depth_clear, bool with_stencil = false);

    virtual ~DepthStencil();
    
  protected:
    DepthStencil();

  private:
    // disabled
    DepthStencil(const DepthStencil& cpy);
    DepthStencil& operator=(const DepthStencil& cpy);
};

#endif /* DEPTH_STENCIL_H */
