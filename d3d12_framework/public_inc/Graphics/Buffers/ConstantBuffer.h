#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

class BufferResourceHeap;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/ShaderResourceDescHeap.h"

/// <summary>
/// Base class for constant buffers
/// </summary>
class ConstantBuffer
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
    static ConstantBuffer* CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT num_bytes);

    virtual ~ConstantBuffer();

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
    virtual void Upload(void* data, UINT start, UINT len) = 0;
    
  protected:
    ConstantBuffer();
    
  private:
    // disabled
    ConstantBuffer(const ConstantBuffer& cpy);
    ConstantBuffer& operator=(const ConstantBuffer& cpy);
};

#endif /* CONSTANT_BUFFER_H */
