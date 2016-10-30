#ifndef D3D12_HEAP_ARRAY_H
#define D3D12_HEAP_ARRAY_H

#include <d3d12.h>
#include "Graphics/Buffers/HeapArray.h"

class D3D12_HeapArray : public HeapArray
{
  public:
    /// <summary>
    /// Creates an array of D3D12 heaps
    /// </summary>
    /// <param name="num_entries">
    /// number of heaps the array is to be able to contain
    /// </param>
    static HeapArray* Create(UINT num_entries);

    ~D3D12_HeapArray();

    /// <summary>
    /// Assigns a descriptor heap to an index in the heap array
    /// </summary>
    /// <param name="index">
    /// index into the heap array to set
    /// </param>
    /// <param name="heap">
    /// heap to store at the index
    /// </param>
    void SetHeap(UINT index, const ShaderResourceDescHeap& heap);

    /// <summary>
    /// Retrieves the number of entries in the array
    /// </summary>
    /// <returns>
    /// number of entries in the array
    /// </returns>
    UINT GetLength() const;

    /// <summary>
    /// Retrieves the array of D3D12 descriptor heaps
    /// </summary>
    /// <returns>
    /// D3D12 descriptor heap array
    /// </returns>
    ID3D12DescriptorHeap** GetArray() const;

  private:
    // disabled
    D3D12_HeapArray();
    D3D12_HeapArray(const D3D12_HeapArray& cpy);
    D3D12_HeapArray& operator=(const D3D12_HeapArray& cpy);

    D3D12_HeapArray(UINT num_entries);

    /// <summary>
    /// number of entries in the heap array
    /// </summary>
    UINT m_len;

    /// <summary>
    /// heap array
    /// </summary>
    ID3D12DescriptorHeap** m_heaps;
};

#endif /* D3D12_HEAP_ARRAY_H */
