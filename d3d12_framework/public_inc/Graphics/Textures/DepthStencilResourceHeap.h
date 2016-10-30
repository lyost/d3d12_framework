#ifndef DEPTH_STENCIL_RESOURCE_HEAP_H
#define DEPTH_STENCIL_RESOURCE_HEAP_H

#include "Graphics/GraphicsCore.h"

class DepthStencilResourceHeap
{
  public:
    /// <summary>
    /// Creates a D3D12 resource heap for depth stencils
    ///</summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num_bytes">
    /// Number of bytes the heap is to contain
    /// </param>
    /// <returns>
    /// pointer to the heap on success
    /// NULL otherwise
    /// </returns>
    static DepthStencilResourceHeap* CreateD3D12(const GraphicsCore& graphics, UINT64 num_bytes);

    virtual ~DepthStencilResourceHeap();

    /// <summary>
    /// Retrieves the number of bytes the heap was created to hold
    ///</summary>
    /// <returns>
    /// number of bytes in the heap
    /// </returns>
    virtual UINT64 GetHeapTotalSize() const = 0;

    /// <summary>
    /// Retrieves the number of bytes the heap used by resources in the heap
    ///</summary>
    /// <returns>
    /// number of bytes used in the heap
    /// </returns>
    virtual UINT64 GetHeapUsedSize() const = 0;

  protected:
    DepthStencilResourceHeap();

  private:
    // disabled
    DepthStencilResourceHeap(const DepthStencilResourceHeap& cpy);
    DepthStencilResourceHeap& operator=(const DepthStencilResourceHeap& cpy);
};

#endif /* DEPTH_STENCIL_RESOURCE_HEAP_H */
