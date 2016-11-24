#ifndef D3D12_SHADER_BUFFER_HEAP_H
#define D3D12_SHADER_BUFFER_HEAP_H

#include <d3d12.h>
#include "Graphics/Buffers/ShaderResourceDescHeap.h"

class D3D12_ShaderResourceDescHeap : public ShaderResourceDescHeap
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
    static D3D12_ShaderResourceDescHeap* Create(const GraphicsCore& graphics, UINT num_descriptors);

    ~D3D12_ShaderResourceDescHeap();

    /// <summary>
    /// Uses the next descriptor in the heap
    ///</summary>
    /// <param name="cpu_handle">
    /// output parameter for the CPU handle to the descriptor
    /// </param>
    /// <param name="gpu_handle">
    /// output parameter for the GPU handle to the descriptor
    /// </param>
    void GetNextDescriptor(D3D12_CPU_DESCRIPTOR_HANDLE& cpu_handle, D3D12_GPU_DESCRIPTOR_HANDLE& gpu_handle);

    /// <summary>
    /// Retrieves the D3D12 descriptor heap
    ///</summary>
    /// <returns>
    /// D3D12 descriptor heap
    /// </returns>
    ID3D12DescriptorHeap* GetHeap() const;

    /// <summary>
    /// Retrieves the number of descriptors in the heap that are in use
    ///</summary>
    /// <returns>
    /// number of descriptors in use
    /// </returns>
    UINT GetNumInUse() const;

    /// <summary>
    /// Retrieves the number of descriptors that the heap was created to contain
    ///</summary>
    /// <returns>
    /// number of descriptors the heap was created to contain
    /// </returns>
    UINT GetNumTotal() const;

  private:
    // disabled
    D3D12_ShaderResourceDescHeap();
    D3D12_ShaderResourceDescHeap(const D3D12_ShaderResourceDescHeap& cpy);
    D3D12_ShaderResourceDescHeap& operator=(const D3D12_ShaderResourceDescHeap& cpy);

    D3D12_ShaderResourceDescHeap(UINT num_descriptors, const D3D12_CPU_DESCRIPTOR_HANDLE& cpu_start, const D3D12_GPU_DESCRIPTOR_HANDLE& gpu_start, UINT descriptor_size, ID3D12DescriptorHeap* heap);

    /// <summary>
    /// Number of descriptors the heap was sized for
    /// </summary>
    UINT m_num_descriptors;

    /// <summary>
    /// Index of the next descriptor to use
    /// </summary>
    UINT m_next_descriptor_index;

    /// <summary>
    /// Handle size of the descriptors
    /// </summary>
    UINT m_descriptor_size;

    /// <summary>
    /// number of bytes the placed resources in the heap have used including alignment
    /// </summary>
    UINT64 m_heap_size;

    /// <summary>
    /// D3D12 descriptor heap
    /// </summary>
    ID3D12DescriptorHeap* m_heap;

    /// <summary>
    /// CPU handle to the start of the descriptor heap
    /// </summary>
    D3D12_CPU_DESCRIPTOR_HANDLE m_cpu_start;

    /// <summary>
    /// GPU handle to the start of the descriptor heap
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE m_gpu_start;
};

#endif /* D3D12_SHADER_BUFFER_HEAP_H */
