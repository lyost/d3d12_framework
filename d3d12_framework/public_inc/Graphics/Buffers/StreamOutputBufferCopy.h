#ifndef STREAMOUTPUTBUFFERCOPY_H
#define STREAMOUTPUTBUFFERCOPY_H

#include "StreamOutputBuffer.h"

/// <summary>
/// Stream output buffer with the ability to copy data to host memory
/// </summary>
class StreamOutputBufferCopy : public StreamOutputBuffer
{
  public:
    /// <summary>
    /// Creates a stream output buffer based on the specified description that
    /// can hold the specified number of elements
    /// </summary>
    /// <param name="graphics">
    /// D3D11 instance to create the buffer for
    /// </param>
    /// <param name="desc">
    /// description of the stream output buffer to create
    /// </param>
    /// <param name="num">
    /// number of elements that the buffer should be able to hold
    /// </param>
    static StreamOutputBufferCopy* Create(D3D11_Core& graphics,
      const StreamOutputBufferDesc& desc,UINT num);
    
    ~StreamOutputBufferCopy();

    /// <summary>
    /// Makes a copy of the stream output buffer's data accessible to the CPU.
    /// When finished with the memory, call EndCopy with the same context.
    /// <remarks>
    /// This function could be implemented to copy the data to host memory
    /// outside of the D3D11 mapped area which would avoid the need to call
    /// EndCopy.  However, due to the performance penalty of copying the data
    /// on the host, this implementation was chosen.
    /// </remarks>
    /// <remarks>
    /// Since this function copies into a D3D11 buffer that is part of the
    /// instance, EndCopy must be called before calling StartCopy again, even
    /// if calling StartCopy with a different context.
    /// </remarks>
    /// </summary>
    /// <param name="context">
    /// D3D11 context to get the data from
    /// </param>
    /// <returns>
    /// Pointer to the start of memory for the buffer.  It is
    /// GetNumEntries() * GetStride() bytes long.
    /// Or NULL if an error occurred.
    /// <remarks>
    /// If NULL is returned, EndCopy doesn't need to be called
    /// </remarks>
    /// </returns>
    void* StartCopy(ID3D11DeviceContext* context) const;
    
    /// <summary>
    /// Informs the instance that memory access started by StartCopy is
    /// complete
    /// </summary>
    /// <param name="context">
    /// D3D11 context that was used with StartCopy
    /// </param>
    void EndCopy(ID3D11DeviceContext* context) const;
    
  private:
    // disabled
    StreamOutputBufferCopy();
    StreamOutputBufferCopy(const StreamOutputBufferCopy& cpy);
    StreamOutputBufferCopy& operator=(const StreamOutputBufferCopy& cpy);
    
    /// <summary>
    /// Creates a stream output buffer
    /// </summary>
    /// <param name="buffer">
    /// D3D11 stream output buffer
    /// </param>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <param name="stride">
    /// number of bytes in each entry
    /// </param>
    /// <param name="slot">
    /// which output buffer slot to use
    /// </param>
    /// <param name="host_buffer">
    /// D3D11 buffer to use for copying data off the GPU
    /// </param>
    StreamOutputBufferCopy(ID3D11Buffer* buffer,UINT num,UINT stride,
      UINT slot,ID3D11Buffer* host_buffer);
    
    /// <summary>
    /// buffer to use for copying data off the GPU
    /// </summary>
    ID3D11Buffer* m_host_buffer;
};

#endif /* STREAMOUTPUTBUFFERCOPY_H */
