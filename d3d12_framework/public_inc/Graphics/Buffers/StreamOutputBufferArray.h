#ifndef STREAM_OUTPUT_BUFFER_ARRAY_H
#define STREAM_OUTPUT_BUFFER_ARRAY_H

class StreamOutputBuffer;

#include <windows.h>
#include "Graphics/Buffers/StreamOutputBuffer.h"

/// <summary>
/// Container of multiple stream output buffers and allows for quickly sending multiple stream output buffers to the stream output stage
/// </summary>
class StreamOutputBufferArray
{
  public:
    /// <summary>
    /// Creates a stream output array with the specified number of elements. The array is initialized to all elements clear of a stream output buffer.
    /// </summary>
    /// <param name="num_buffers">
    /// number of buffers that will be in the array
    /// </param>
    /// <returns>
    /// pointer to the stream output buffer array instance on success
    /// NULL on error
    /// </returns>
    static StreamOutputBufferArray* CreateD3D12(UINT num_buffers);
    
    virtual ~StreamOutputBufferArray();
    
    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a stream output buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    virtual void Set(UINT index, const StreamOutputBuffer& buffer) = 0;
    
    /// <summary>
    /// Removes any stream output buffer from the specified index
    /// </summary>
    /// <param name="index">
    /// which index to clear
    /// </param>
    virtual void Clear(UINT index) = 0;

    /// <summary>
    /// Retrieves the number of buffers the array was created to hold
    /// </summary>
    /// <returns>
    /// number of entries in the array
    /// </returns>
    virtual UINT GetNumBuffers() const = 0;

  protected:
    StreamOutputBufferArray();
    
  private:
    // disabled
    StreamOutputBufferArray(const StreamOutputBufferArray& cpy);
    StreamOutputBufferArray& operator=(const StreamOutputBufferArray& cpy);
};

#endif /* STREAM_OUTPUT_BUFFER_ARRAY_H */
