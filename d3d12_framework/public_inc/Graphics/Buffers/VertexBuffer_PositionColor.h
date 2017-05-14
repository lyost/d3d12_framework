#ifndef VERTEXBUFFER_POSITION_COLOR_H
#define VERTEXBUFFER_POSITION_COLOR_H

class VertexBufferGPU_PositionColor;

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/VertexBufferGPU_PositionColor.h"
#include "Graphics/VertexDeclarations/Vertex_PositionColor.h"

/// <summary>
/// Vertex buffer whose elements are position and rgba color values
/// </summary>
class VertexBuffer_PositionColor : public VertexBuffer
{
  public:
    /// <summary>
    /// Creates a vertex buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <param name="data">
    /// initial data for the vertex buffer
    /// </param>
    /// <returns>
    /// pointer to the vertex buffer instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static VertexBuffer_PositionColor* CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionColor* data);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBuffer_PositionColor();

    /// <summary>
    /// Updates the data in the vertex buffer starting at the specified index
    /// </summary>
    /// <param name="buffer_start_index">
    /// index of the Vertex_PositionColor in the vertex buffer to start writing data to
    /// </param>
    /// <param name="data">
    /// data to write to the vertex buffer
    /// </param>
    /// <param name="num_entries">
    /// number of entries to write to the vertex buffer
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void Upload(UINT buffer_start_index, const Vertex_PositionColor* data, UINT num_entries) = 0;

    /// <summary>
    /// Preps the command list for uploading the contents of the vertex buffer to the specified GPU-only accessible vertex buffer.  The command list must execute followed by a fence for the transfer to be
    /// completed.
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="command_list">
    /// command list to use for uploading
    /// </param>
    /// <param name="buffer">
    /// GPU-only vertex buffer to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, const VertexBufferGPU_PositionColor& buffer) = 0;

  protected:
    VertexBuffer_PositionColor();
    
  private:
    // disabled
    VertexBuffer_PositionColor(const VertexBuffer_PositionColor& cpy);
    VertexBuffer_PositionColor& operator=( const VertexBuffer_PositionColor& cpy);
};

#endif /* VERTEXBUFFER_POSITION_COLOR_H */
