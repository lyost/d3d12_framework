#ifndef VERTEXBUFFER_POSITION_H
#define VERTEXBUFFER_POSITION_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"
#include "Graphics/VertexDeclarations/Vertex_Position.h"

/// <summary>
/// Vertex buffer whose only element is position
/// </summary>
class VertexBuffer_Position : public VertexBuffer
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
    static VertexBuffer_Position* CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_Position* data);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBuffer_Position();

  protected:
    VertexBuffer_Position();
    
  private:
    // disabled
    VertexBuffer_Position(const VertexBuffer_Position& cpy);
    VertexBuffer_Position& operator=( const VertexBuffer_Position& cpy);
};

#endif /* VERTEXBUFFER_POSITION_H */
