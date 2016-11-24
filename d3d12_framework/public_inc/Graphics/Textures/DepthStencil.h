#ifndef DEPTH_STENCIL_H
#define DEPTH_STENCIL_H

class DepthStencilResourceHeap;
class DepthStencilDescHeap;
#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/DepthStencilDescHeap.h"
#include "Graphics/Textures/DepthStencilResourceHeap.h"

class DepthStencil
{
  public:
    /// <summary>
    /// Determines the size depth stencil will need to be to hold the requested number of bytes
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
    /// <returns>
    /// number of bytes the depth stencil should be created with
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static UINT GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height);

    /// <summary>
    /// Creates a D3D12 depth stencil
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="resource_heap">
    /// depth stencil resource heap to put the depth stencil into
    /// <remarks>
    /// It is the caller's responsibility to make sure there is enough room in the heap for the new buffer
    /// </remarks>
    /// </param>
    /// <param name="depth_stencil_buffer_heap">
    /// depth stencil resources descriptor heap that the depth stencil will be accessed from
    /// <remarks>
    /// It is the caller's responsibility to make sure there is enough room in the heap for the new buffer
    /// </remarks>
    /// </param>
    /// <param name="width">
    /// width of the depth stencil in pixels
    /// </param>
    /// <param name="height">
    /// height of the depth stencil in pixels
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
    static DepthStencil* CreateD3D12(const GraphicsCore& graphics, DepthStencilResourceHeap& resource_heap, DepthStencilDescHeap& depth_stencil_buffer_heap, UINT width, UINT height,
      float default_depth_clear);

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
