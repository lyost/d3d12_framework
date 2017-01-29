#ifndef READBACK_BUFFER_H
#define READBACK_BUFFER_H

#include "Graphics/GraphicsCore.h"

/// <summary>
/// Base class for buffers that copy data from the graphic card's memory (or driver's memory) to host memory
/// </summary>
class ReadbackBuffer
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
    static ReadbackBuffer* CreateD3D12(const GraphicsCore& graphics, UINT num_bytes);

    virtual ~ReadbackBuffer();

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
    virtual void Upload(void* data, UINT start, UINT len) = 0; // todo: update this to something that makes sense or remove it
    
  protected:
    ReadbackBuffer();
    
  private:
    // disabled
    ReadbackBuffer(const ReadbackBuffer& cpy);
    ReadbackBuffer& operator=(const ReadbackBuffer& cpy);
};

#endif /* READBACK_BUFFER_H */
