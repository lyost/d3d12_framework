#ifndef TEXTURE_RESOURCE_HEAP_H
#define TEXTURE_RESOURCE_HEAP_H

#include "Graphics/GraphicsCore.h"

class TextureResourceHeap
{
  public:
    /// <summary>
    /// Creates a D3D12 resource heap for textures
    ///</summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num_bytes">
    /// Number of bytes the heap is to contain
    /// </param>
    /// <returns>
    /// pointer to the heap
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureResourceHeap* CreateD3D12(const GraphicsCore& graphics, UINT64 num_bytes);

    virtual ~TextureResourceHeap();

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
    TextureResourceHeap();

  private:
    // disabled
    TextureResourceHeap(const TextureResourceHeap& cpy);
    TextureResourceHeap& operator=(const TextureResourceHeap& cpy);
};

#endif /* TEXTURE_RESOURCE_HEAP_H */
