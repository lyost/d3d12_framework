#ifndef HEAP_ARRAY_H
#define HEAP_ARRAY_H

class ShaderResourceDescHeap;
#include "Graphics/ShaderResourceDescHeap.h"

class HeapArray
{
  public:
    /// <summary>
    /// Creates an array of D3D12 heaps
    /// </summary>
    /// <param name="num_entries">
    /// number of heaps the array is to be able to contain
    /// </param>
    static HeapArray* CreateD3D12(UINT num_entries);

    virtual ~HeapArray();

    /// <summary>
    /// Assigns a descriptor heap to an index in the heap array
    /// </summary>
    /// <param name="index">
    /// index into the heap array to set
    /// </param>
    /// <param name="heap">
    /// heap to store at the index
    /// </param>
    virtual void SetHeap(UINT index, const ShaderResourceDescHeap& heap) = 0;

  protected:
    HeapArray();

  private:
    // disabled
    HeapArray(const HeapArray& cpy);
    HeapArray& operator=(const HeapArray& cpy);
};

#endif /* HEAP_ARRAY_H */
