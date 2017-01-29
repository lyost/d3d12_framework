#ifndef STREAM_OUTPUT_BUFFER_H
#define STREAM_OUTPUT_BUFFER_H

class ReadbackBuffer;

#include <vector>
#include "Graphics/GraphicsCore.h"
#include "Graphics/StreamOutputConfig.h"
#include "Graphics/CommandList.h"
#include "Graphics/Buffers/ReadbackBuffer.h"

/// <summary>
/// Buffer for stream output that can also be used as a vertex buffer
/// </summary>
class StreamOutputBuffer
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
    static StreamOutputBuffer* CreateD3D12(GraphicsCore& graphics, const StreamOutputConfig& so_config, UINT stream_index, UINT num_vertices);

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
    static void GetNumVerticesWrittenD3D12(GraphicsCore& graphics, CommandList& command_list, const std::vector<StreamOutputBuffer*> so_buffers, ReadbackBuffer& readback_buffer,
      std::vector<UINT>& num_vertices);
    
    virtual ~StreamOutputBuffer();

    /// <summary>
    /// Retrieves the number of vertices that can fit into the buffer
    /// </summary>
    /// <returns>
    /// number of vertices the buffer can hold
    /// </returns>
    virtual UINT GetVertexCapacity() const = 0;

  protected:
    StreamOutputBuffer();
    
  private:
    // disabled
    StreamOutputBuffer(const StreamOutputBuffer& cpy);
    StreamOutputBuffer& operator=( const StreamOutputBuffer& cpy);
};

#endif /* STREAM_OUTPUT_BUFFER_H */
