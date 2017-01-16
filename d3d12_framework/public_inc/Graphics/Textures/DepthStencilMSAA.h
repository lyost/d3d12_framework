#ifndef DEPTH_STENCIL_MSAA_H
#define DEPTH_STENCIL_MSAA_H

#include "Graphics/GraphicsCore.h"

class DepthStencilMSAA
{
  public:
    /// <summary>
    /// Creates a D3D12 MSAA depth stencil
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
    /// <param name="sample_count">
    /// number of multisamples per pixel
    /// </param>
    /// <param name="quality">
    /// image quality level
    /// </param>
    /// <param name="default_depth_clear">
    /// default value to use for clearing the depth stencil
    /// </param>
    /// <returns>
    /// D3D12 depth stencil
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static DepthStencilMSAA* CreateD3D12(const GraphicsCore& graphics, UINT width, UINT height, UINT sample_count, UINT quality, float default_depth_clear);

    virtual ~DepthStencilMSAA();
    
  protected:
    DepthStencilMSAA();

  private:
    // disabled
    DepthStencilMSAA(const DepthStencilMSAA& cpy);
    DepthStencilMSAA& operator=(const DepthStencilMSAA& cpy);
};

#endif /* DEPTH_STENCIL_MSAA_H */
