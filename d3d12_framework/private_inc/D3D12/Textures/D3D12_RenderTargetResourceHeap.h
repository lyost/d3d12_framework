#ifndef D3D12_RENDER_TARGET_RESOURCE_HEAP_H
#define D3D12_RENDER_TARGET_RESOURCE_HEAP_H

#include <d3d12.h>
#include "Graphics/Textures/TextureResourceHeap.h"

class D3D12_RenderTargetResourceHeap
{
  public:
    /// <summary>
    /// Creates a D3D12 placed resource heap for render targets
    ///</summary>
    /// <param name="device">
    /// D3D12 device
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
    static D3D12_RenderTargetResourceHeap* Create(ID3D12Device* device, UINT64 num_bytes);

    ~D3D12_RenderTargetResourceHeap();

    /// <summary>
    /// Creates a placed resource in the heap
    ///</summary>
    /// <param name="device">
    /// D3D12 device
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
    ID3D12Resource* CreateResource(ID3D12Device* device, const D3D12_RESOURCE_DESC& resource_desc);

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
    D3D12_RenderTargetResourceHeap();
    D3D12_RenderTargetResourceHeap(const D3D12_RenderTargetResourceHeap& cpy);
    D3D12_RenderTargetResourceHeap& operator=(const D3D12_RenderTargetResourceHeap& cpy);

    D3D12_RenderTargetResourceHeap(UINT64 num_bytes, ID3D12Heap* heap);

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

#endif /* D3D12_RENDER_TARGET_RESOURCE_HEAP_H */
