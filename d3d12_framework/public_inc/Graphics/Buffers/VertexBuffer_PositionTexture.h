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
    /// pointer to the vertex buffer instance on success
    /// NULL on error
    /// </returns>
    static VertexBuffer_PositionTexture* CreateD3D12(GraphicsCore& graphics, UINT num, const Vertex_PositionTexture* data);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBuffer_PositionTexture();

  protected:
    VertexBuffer_PositionTexture();
    
  private:
    // disabled
    VertexBuffer_PositionTexture(const VertexBuffer_PositionTexture& cpy);
    VertexBuffer_PositionTexture& operator=( const VertexBuffer_PositionTexture& cpy);
};

#endif /* VERTEXBUFFER_POSITIONTEXTURE_H */
