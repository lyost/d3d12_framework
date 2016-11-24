#ifndef SHADER_RESOURCE_DESC_HEAP_H
#define SHADER_RESOURCE_DESC_HEAP_H

#include "Graphics/GraphicsCore.h"

class ShaderResourceDescHeap
{
  public:
    /// <summary>
    /// Creates a D3D12 descriptor heap for constant buffers, textures, and unordered access views
    ///</summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num_descriptors">
    /// Number of descriptors the heap is to contain
    /// </param>
    /// <returns>
    /// pointer to the descriptor heap
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static ShaderResourceDescHeap* CreateD3D12(const GraphicsCore& graphics, UINT num_descriptors);

    virtual ~ShaderResourceDescHeap();

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
    ShaderResourceDescHeap();

  private:
    // disabled
    ShaderResourceDescHeap(const ShaderResourceDescHeap& cpy);
    ShaderResourceDescHeap& operator=(const ShaderResourceDescHeap& cpy);
};

#endif /* SHADER_RESOURCE_DESC_HEAP_H */
