#ifndef D3D12_TEXTURE_RESOURCE_HEAP_H
#define D3D12_TEXTURE_RESOURCE_HEAP_H

#include <d3d12.h>
#include "Graphics/Textures/TextureResourceHeap.h"

class D3D12_TextureResourceHeap : public TextureResourceHeap
{
  public:
    /// <summary>
    /// Creates a D3D12 placed resource heap for textures
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
    static D3D12_TextureResourceHeap* Create(const GraphicsCore& graphics, UINT64 num_bytes);

    ~D3D12_TextureResourceHeap();

    /// <summary>
    /// Creates a placed resource in the heap
    ///</summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="resource_desc">
    /// D3D12 description of the resource to create
    /// </param>
    /// <returns>
    /// pointer to the D3D12 resource
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    ID3D12Resource* CreateResource(const GraphicsCore& graphics, const D3D12_RESOURCE_DESC& resource_desc);

    /// <summary>
    /// Retrieves the number of bytes the heap was created to hold
    ///</summary>
    /// <returns>
    /// number of bytes in the heap
    /// </returns>
    UINT64 GetHeapTotalSize() const;

    /// <summary>
    /// Retrieves the number of bytes the heap used by resources in the heap
    ///</summary>
    /// <returns>
    /// number of bytes used in the heap
    /// </returns>
    UINT64 GetHeapUsedSize() const;

  private:
    // disabled
    D3D12_TextureResourceHeap();
    D3D12_TextureResourceHeap(const D3D12_TextureResourceHeap& cpy);
    D3D12_TextureResourceHeap& operator=(const D3D12_TextureResourceHeap& cpy);

    D3D12_TextureResourceHeap(UINT64 num_bytes, ID3D12Heap* heap);

    /// <summary>
    /// number of bytes the heap was created for
    /// </summary>
    UINT64 m_heap_total_size;

    /// <summary>
    /// number of bytes the placed resources in the heap have used including alignment
    /// </summary>
    UINT64 m_heap_used_size;

    /// <summary>
    /// D3D12 heap
    /// </summary>
    ID3D12Heap* m_heap;
};

#endif /* D3D12_TEXTURE_RESOURCE_HEAP_H */
