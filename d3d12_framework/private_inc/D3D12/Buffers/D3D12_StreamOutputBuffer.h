#ifndef D3D12_STREAM_OUTPUT_BUFFER_H
#define D3D12_STREAM_OUTPUT_BUFFER_H

#include <d3d12.h>
#include "Graphics/Buffers/StreamOutputBuffer.h"

class D3D12_StreamOutputBuffer : public StreamOutputBuffer
{
  public:
    /// <summary>
    /// Creates a stream output buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="so_config">
    /// configuration of the stream output stage
    /// </param>
    /// <param name="stream_index">
    /// index of the output stream to create a buffer for
    /// </param>
    /// <param name="num_vertices">
    /// number of vertices the buffer should be able to contain
    /// </param>
    /// <returns>
    /// pointer to the stream output buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static StreamOutputBuffer* Create(GraphicsCore& graphics, const StreamOutputConfig& so_config, UINT stream_index, UINT num_vertices);

    /// <summary>
    /// Retrieves the number of vertices written to the various stream output buffers
    /// <remarks>
    /// This takes a collection of stream output buffers since the command list will need to be executed which means waiting for a fence (all of this is done internally to the function), so it is more
    /// efficient to do this on multiple buffers instead of individually.
    /// </remarks>
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="command_list">
    /// command list to use.
    /// <remarks>
    /// This should be closed when passed in
    /// </remarks>
    /// </param>
    /// <param name="so_buffers">
    /// stream output buffers to determine how many vertices were written to each the last time they were written to
    /// </param>
    /// <param name="readback_buffer">
    /// readback buffer to overwrite for temporary storage
    /// <remarks>
    /// Must be able to contain at least sizeof(UINT64) * so_buffers.size() in bytes
    /// </remarks>
    /// </param>
    /// <param name="num_vertices">
    /// where to put the number of vertices in each stream output buffer.  This will be appended to in the same order that buffers are in so_buffers
    /// </param>
    static void GetNumVerticesWritten(GraphicsCore& graphics, CommandList& command_list, const std::vector<StreamOutputBuffer*> so_buffers, ReadbackBuffer& readback_buffer,
      std::vector<UINT>& num_vertices);
    
    ~D3D12_StreamOutputBuffer();

    /// <summary>
    /// Retrieves the number of vertices that can fit into the buffer
    /// </summary>
    /// <returns>
    /// number of vertices the buffer can hold
    /// </returns>
    UINT GetVertexCapacity() const;

    /// <summary>
    /// Retrieves stream output buffer view of the buffer
    /// </summary>
    /// <returns>
    /// stream output view
    /// </returns>
    const D3D12_STREAM_OUTPUT_BUFFER_VIEW& GetStreamOutputBufferView() const;

    /// <summary>
    /// Retrieves vertex buffer view of the buffer
    /// </summary>
    /// <returns>
    /// stream output view
    /// </returns>
    const D3D12_VERTEX_BUFFER_VIEW& GetVertexBufferView() const;

    /// <summary>
    /// Retrieves the D3D12 resource of the stream output buffer
    /// </summary>
    /// <returns>
    /// D3D12 resource for the stream output buffer
    /// </returns>
    ID3D12Resource* GetResource() const;
    
  private:
    // disabled
    D3D12_StreamOutputBuffer();
    D3D12_StreamOutputBuffer(const D3D12_StreamOutputBuffer& cpy);
    D3D12_StreamOutputBuffer& operator=(const D3D12_StreamOutputBuffer& cpy);

    D3D12_StreamOutputBuffer(ID3D12Resource* buffer, const D3D12_STREAM_OUTPUT_BUFFER_VIEW& so_view, const D3D12_VERTEX_BUFFER_VIEW& vb_view, UINT num_vertices);

    /// <summary>
    /// buffer resource
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// stream output buffer view
    /// </summary>
    D3D12_STREAM_OUTPUT_BUFFER_VIEW m_so_view;

    /// <summary>
    /// vertex buffer view, used to provide data to the command list for rendering
    /// </summary>
    D3D12_VERTEX_BUFFER_VIEW m_vb_view;

    /// <summary>
    /// number of vertices that can fit into the buffer
    /// </summary>
    UINT m_num_vertices;
};

#endif /* D3D12_STREAM_OUTPUT_BUFFER_H */
