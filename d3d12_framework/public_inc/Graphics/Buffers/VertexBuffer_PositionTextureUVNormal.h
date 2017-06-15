#ifndef VERTEXBUFFER_POSITIONTEXTURE_UV_NORMAL_H
#define VERTEXBUFFER_POSITIONTEXTURE_UV_NORMAL_H

class VertexBufferGPU_PositionTextureUVNormal;

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/Buffers/VertexBufferGPU_PositionTextureUVNormal.h"
#include "Graphics/VertexDeclarations/Vertex_PositionTexture.h"

/// <summary>
/// Vertex buffer whose elements are position, texture uv coordinates, and a 3d normal vector
/// </summary>
class VertexBuffer_PositionTextureUVNormal : public VertexBuffer
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
    static VertexBuffer_PositionTextureUVNormal* CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUVNormal* data);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBuffer_PositionTextureUVNormal();

    /// <summary>
    /// Updates the data in the vertex buffer starting at the specified index
    /// </summary>
    /// <param name="buffer_start_index">
    /// index of the Vertex_PositionTextureU in the vertex buffer to start writing data to
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
    virtual void Upload(UINT buffer_start_index, const Vertex_PositionTextureUVNormal* data, UINT num_entries) = 0;

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
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, const VertexBufferGPU_PositionTextureUVNormal& buffer) = 0;

  protected:
    VertexBuffer_PositionTextureUVNormal();
    
  private:
    // disabled
    VertexBuffer_PositionTextureUVNormal(const VertexBuffer_PositionTextureUVNormal& cpy);
    VertexBuffer_PositionTextureUVNormal& operator=( const VertexBuffer_PositionTextureUVNormal& cpy);
};

#endif /* VERTEXBUFFER_POSITIONTEXTURE_UV_NORMAL_H */
