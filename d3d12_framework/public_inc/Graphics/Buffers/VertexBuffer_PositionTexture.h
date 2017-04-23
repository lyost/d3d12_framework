#ifndef VERTEXBUFFER_POSITIONTEXTURE_H
#define VERTEXBUFFER_POSITIONTEXTURE_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/VertexDeclarations/Vertex_PositionTexture.h"

/// <summary>
/// Vertex buffer whose elements are position and texture values
/// </summary>
class VertexBuffer_PositionTexture : public VertexBuffer
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
    static VertexBuffer_PositionTexture* CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureU* data);

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
    static VertexBuffer_PositionTexture* CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUV* data);

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
    static VertexBuffer_PositionTexture* CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTextureUVW* data);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBuffer_PositionTexture();

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
    virtual void Upload(UINT buffer_start_index, const Vertex_PositionTextureU* data, UINT num_entries) = 0;

    /// <summary>
    /// Updates the data in the vertex buffer starting at the specified index
    /// </summary>
    /// <param name="buffer_start_index">
    /// index of the Vertex_PositionTextureUV in the vertex buffer to start writing data to
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
    virtual void Upload(UINT buffer_start_index, const Vertex_PositionTextureUV* data, UINT num_entries) = 0;

    /// <summary>
    /// Updates the data in the vertex buffer starting at the specified index
    /// </summary>
    /// <param name="buffer_start_index">
    /// index of the Vertex_PositionTextureUVW in the vertex buffer to start writing data to
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
    virtual void Upload(UINT buffer_start_index, const Vertex_PositionTextureUVW* data, UINT num_entries) = 0;

  protected:
    VertexBuffer_PositionTexture();
    
  private:
    // disabled
    VertexBuffer_PositionTexture(const VertexBuffer_PositionTexture& cpy);
    VertexBuffer_PositionTexture& operator=( const VertexBuffer_PositionTexture& cpy);
};

#endif /* VERTEXBUFFER_POSITIONTEXTURE_H */
