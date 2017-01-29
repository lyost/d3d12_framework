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
    /// Creates a D3D12 constant buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="shader_buffer_heap">
    /// shader resources descriptor heap that the constant buffer will be accessed from
    /// </param>
    /// <param name="num_bytes">
    /// size of the buffer to allocate in bytes
    /// </param>
    /// <returns>
    /// D3D12 constant buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static D3D12_ConstantBuffer* Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT num_bytes);

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

    /// <summary>
    /// Retrieves the D3D12 resource of the buffer
    /// </summary>
    /// <returns>
    /// D3D12 resource for the buffer
    /// </returns>
    ID3D12Resource* GetResource() const;
    
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
    static void GetResourceDesc(UINT& num_bytes, D3D12_RESOURCE_DESC& resource_desc);

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
