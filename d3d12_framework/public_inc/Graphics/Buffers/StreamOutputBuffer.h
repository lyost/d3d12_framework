#ifndef STREAM_OUTPUT_BUFFER_H
#define STREAM_OUTPUT_BUFFER_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/StreamOutputConfig.h"

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
