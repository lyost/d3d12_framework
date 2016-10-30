#ifndef RESOURCE_HEAP_H
#define RESOURCE_HEAP_H

#include "Graphics/GraphicsCore.h"

class BufferResourceHeap
{
  public:
    /// <summary>
    /// Creates a D3D12 resource heap
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
    static BufferResourceHeap* CreateD3D12(const GraphicsCore& graphics, UINT64 num_bytes);

    virtual ~BufferResourceHeap();

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
    BufferResourceHeap();

  private:
    // disabled
    BufferResourceHeap(const BufferResourceHeap& cpy);
    BufferResourceHeap& operator=(const BufferResourceHeap& cpy);
};

#endif /* RESOURCE_HEAP_H */
