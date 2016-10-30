#ifndef DEPTH_STENCIL_DESC_HEAP_H
#define DEPTH_STENCIL_DESC_HEAP_H

#include "Graphics/GraphicsCore.h"

class DepthStencilDescHeap
{
  public:
    /// <summary>
    /// Creates a D3D12 depth stencil descriptor heap
    ///</summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num_descriptors">
    /// Number of descriptors the heap is to contain
    /// </param>
    /// <returns>
    /// pointer to the descriptor heap on success
    /// NULL otherwise
    /// </returns>
    static DepthStencilDescHeap* CreateD3D12(const GraphicsCore& graphics, UINT num_descriptors);

    virtual ~DepthStencilDescHeap();

    /// <summary>
    /// Retrieves the number of descriptors in the heap that are in use
    ///</summary>
    /// <returns>
    /// number of descriptors in use
    /// </returns>
    virtual UINT GetNumInUse() const = 0;

    /// <summary>
    /// Retrieves the number of descriptors that the heap was created to contain
    ///</summary>
    /// <returns>
    /// number of descriptors the heap was created to contain
    /// </returns>
    virtual UINT GetNumTotal() const = 0;

  protected:
    DepthStencilDescHeap();

  private:
    // disabled
    DepthStencilDescHeap(const DepthStencilDescHeap& cpy);
    DepthStencilDescHeap& operator=(const DepthStencilDescHeap& cpy);
};

#endif /* DEPTH_STENCIL_DESC_HEAP_H */
