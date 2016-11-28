#ifndef CONSTANT_BUFFER_H
#define CONSTANT_BUFFER_H

class BufferResourceHeap;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/BufferResourceHeap.h"
#include "Graphics/ShaderResourceDescHeap.h"

/// <summary>
/// Base class for constant buffers
/// </summary>
class ConstantBuffer
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
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
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
    /// D3D12 constant buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static ConstantBuffer* CreateD3D12(const GraphicsCore& graphics, BufferResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT num_bytes);

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
