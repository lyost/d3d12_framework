#ifndef D3D12_STREAM_OUTPUT_BUFFER_ARRAY_H
#define D3D12_STREAM_OUTPUT_BUFFER_ARRAY_H

#include <d3d12.h>
#include "Graphics/Buffers/StreamOutputBufferArray.h"

class D3D12_StreamOutputBufferArray : public StreamOutputBufferArray
{
  public:
    /// <summary>
    /// Creates a stream output buffer array with the specified number of elements. The array is initialized to all elements clear of a stream output buffer.
    /// </summary>
    /// <param name="num_buffers">
    /// number of buffers that will be in the array
    /// </param>
    D3D12_StreamOutputBufferArray(UINT num_buffers);
    
    ~D3D12_StreamOutputBufferArray();
    
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
    void Set(UINT index, const StreamOutputBuffer& buffer);
    
    /// <summary>
    /// Removes any stream output buffer from the specified index
    /// </summary>
    /// <param name="index">
    /// which index to clear
    /// </param>
    void Clear(UINT index);

    /// <summary>
    /// Retrieves the number of buffers the array was created to hold
    /// </summary>
    /// <returns>
    /// number of entries in the array
    /// </returns>
    UINT GetNumBuffers() const;

    /// <summary>
    /// Retrieves the array of D3D12 buffers
    /// </summary>
    /// <returns>
    /// D3D12 array of the buffers
    /// </returns>
    const D3D12_STREAM_OUTPUT_BUFFER_VIEW* GetArray() const;
    
  private:
    // disabled
    D3D12_StreamOutputBufferArray();
    D3D12_StreamOutputBufferArray(const D3D12_StreamOutputBufferArray& cpy);
    D3D12_StreamOutputBufferArray& operator=(const D3D12_StreamOutputBufferArray& cpy);
    
    /// <summary>
    /// D3D12 vertex buffers
    /// </summary>
    D3D12_STREAM_OUTPUT_BUFFER_VIEW* m_buffers;
    
    /// <summary>
    /// number of elements in m_buffers
    /// </summary>
    UINT m_num;
};

#endif /* D3D12_STREAM_OUTPUT_BUFFER_ARRAY_H */
