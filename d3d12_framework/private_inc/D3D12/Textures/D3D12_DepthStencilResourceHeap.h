#ifndef D3D12_DEPTH_STENCIL_RESOURCE_HEAP_H
#define D3D12_DEPTH_STENCIL_RESOURCE_HEAP_H

#include <d3d12.h>
#include "Graphics/Textures/DepthStencilResourceHeap.h"

class D3D12_DepthStencilResourceHeap : public DepthStencilResourceHeap
{
  public:
    /// <summary>
    /// Creates a D3D12 placed resource heap for depth stencils
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
    static D3D12_DepthStencilResourceHeap* Create(const GraphicsCore& graphics, UINT64 num_bytes);

    ~D3D12_DepthStencilResourceHeap();

    /// <summary>
    /// Creates a placed resource in the heap
    ///</summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="resource_desc">
    /// D3D12 description of the resource to create
    /// </param>
    /// <param name="default_depth_clear">
    /// default value to use for clearing the depth stencil
    /// </param>
    /// <returns>
    /// pointer to the D3D12 resource on success
    /// NULL otherwise
    /// </returns>
    ID3D12Resource* CreateResource(const GraphicsCore& graphics, const D3D12_RESOURCE_DESC& resource_desc, float default_depth_clear);

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
    D3D12_DepthStencilResourceHeap();
    D3D12_DepthStencilResourceHeap(const D3D12_DepthStencilResourceHeap& cpy);
    D3D12_DepthStencilResourceHeap& operator=(const D3D12_DepthStencilResourceHeap& cpy);

    D3D12_DepthStencilResourceHeap(UINT64 num_bytes, ID3D12Heap* heap);

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

#endif /* D3D12_DEPTH_STENCIL_RESOURCE_HEAP_H */
