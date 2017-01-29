#ifndef D3D12_READBACK_BUFFER_H
#define D3D12_READBACK_BUFFER_H

#include <d3d12.h>
#include "Graphics/Buffers/ReadbackBuffer.h"

/// <summary>
/// Wrapper for D3D12 readback buffers
/// </summary>
class D3D12_ReadbackBuffer : public ReadbackBuffer
{
  public:
    /// <summary>
    /// Creates a D3D12 readback buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num_bytes">
    /// size of the buffer to allocate in bytes
    /// </param>
    /// <returns>
    /// D3D12 readback buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static D3D12_ReadbackBuffer* Create(const GraphicsCore& graphics, UINT num_bytes);

    ~D3D12_ReadbackBuffer();

    /// <summary>
    /// Retrieves the D3D12 resource of the buffer
    /// </summary>
    /// <returns>
    /// D3D12 resource for the buffer
    /// </returns>
    ID3D12Resource* GetResource() const;

    /// <summary>
    /// Maps the buffer into host memory
    /// <summary>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void Map();

    /// <summary>
    /// Retrieves the host memory address to the beginning of the buffer
    /// <summary>
    /// <returns>
    /// start of the buffer's host memory
    /// </returns>
    UINT8* GetHostMemStart() const;

    /// <summary>
    /// Unmaps the buffer from host memory
    /// <summary>
    void Unmap();
    
  private:
    // disabled
    D3D12_ReadbackBuffer();
    D3D12_ReadbackBuffer(const D3D12_ReadbackBuffer& cpy);
    D3D12_ReadbackBuffer& operator=(const D3D12_ReadbackBuffer& cpy);

    D3D12_ReadbackBuffer(ID3D12Resource* buffer, UINT num_bytes);

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
    /// number of bytes in the buffer
    /// </summary>
    UINT m_num_bytes;
};

#endif /* D3D12_READBACK_BUFFER_H */
