#ifndef D3D12_CONSTANT_BUFFER_H
#define D3D12_CONSTANT_BUFFER_H

#include <d3d12.h>
#include "Graphics/Buffers/ConstantBuffer.h"

/// <summary>
/// Wrapper for D3D12 constant buffers
/// </summary>
class D3D12_ConstantBuffer : public ConstantBuffer
{
  public:
    /// <summary>
    /// Determines the size a constant buffer will need to be to hold the requested number of bytes
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num_bytes">
    /// desired number of bytes to have in a constant buffer
    /// </param>
    /// <returns>
    /// number of bytes the constant buffer should be created with
    /// -1 if the computed size is too large
    /// </returns>
    static UINT GetAlignedSize(const GraphicsCore& graphics, UINT num_bytes);

    /// <summary>
    /// Creates a D3D12 constant buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="resource_heap">
    /// resource heap to put the constant buffer's memory into
    /// <remarks>
    /// It is the caller's responsibility to make sure there is enough room in the heap for the new buffer
    /// </remarks>
    /// </param>
    /// <param name="shader_buffer_heap">
    /// shader resources descriptor heap that the constant buffer will be accessed from
    /// <remarks>
    /// It is the caller's responsibility to make sure there is enough room in the heap for the new buffer
    /// </remarks>
    /// </param>
    /// <param name="num_bytes">
    /// size of the buffer to allocate in bytes
    /// <remarks>
    /// Must be the return value of GetAlignedSize
    /// </remarks>
    /// </param>
    /// <returns>
    /// D3D12 constant buffer on success
    /// NULL on error
    /// </returns>
    static D3D12_ConstantBuffer* Create(const GraphicsCore& graphics, BufferResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT num_bytes);

    ~D3D12_ConstantBuffer();

    /// <summary>
    /// Updates part of the constant buffer
    /// </summary>
    /// <param name="data">
    /// data to upload to the constant buffer
    /// <remarks>
    /// This must be at least len bytes long
    /// </remarks>
    /// </param>
    /// <param name="start">
    /// index of the first byte in the contant buffer to write to
    /// </param>
    /// <param name="len">
    /// number ofbytes to write to the constant buffer
    /// </param>
    void Upload(void* data, UINT start, UINT len);

    /// <summary>
    /// Retrieves the GPU address for the buffer
    /// </summary>
    /// <returns>
    /// GPU address for the buffer
    /// </returns>
    D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddr() const;
    
  private:
    // disabled
    D3D12_ConstantBuffer();
    D3D12_ConstantBuffer(const D3D12_ConstantBuffer& cpy);
    D3D12_ConstantBuffer& operator=(const D3D12_ConstantBuffer& cpy);

    D3D12_ConstantBuffer(ID3D12Resource* buffer, UINT8* host_mem_start, D3D12_GPU_VIRTUAL_ADDRESS gpu_mem, UINT num_bytes);

    /// <summary>
    /// Helper function to fill in a D3D12 resource description struct
    /// </summary>
    /// <param name="num_bytes">
    /// desired number of bytes to have in a constant buffer
    /// </param>
    /// <param name="resource_desc">
    /// output paramenter of the resource description struct to fill in
    /// </param>
    static void GetResourceDesc(UINT num_bytes, D3D12_RESOURCE_DESC& resource_desc);

    /// <summary>
    /// D3D12 constant buffer resource
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// pointer to the start of the host mapped buffer
    /// </summary>
    UINT8* m_host_mem_start;

    /// <summary>
    /// GPU address for the buffer
    /// </summary>
    D3D12_GPU_VIRTUAL_ADDRESS m_gpu_mem;

    /// <summary>
    /// number of bytes in the buffer
    /// </summary>
    UINT m_num_bytes;
};

#endif /* D3D12_CONSTANT_BUFFER_H */
