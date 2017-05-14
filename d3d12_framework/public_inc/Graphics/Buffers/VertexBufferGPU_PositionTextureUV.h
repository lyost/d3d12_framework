#ifndef VERTEXBUFFER_GPU_POSITIONTEXTURE_UV_H
#define VERTEXBUFFER_GPU_POSITIONTEXTURE_UV_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"

/// <summary>
/// Vertex buffer whose elements are position and texture values
/// </summary>
class VertexBufferGPU_PositionTextureUV : public VertexBuffer
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
    /// <returns>
    /// pointer to the vertex buffer instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static VertexBufferGPU_PositionTextureUV* CreateD3D12(GraphicsCore& graphics, UINT num);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBufferGPU_PositionTextureUV();

  protected:
    VertexBufferGPU_PositionTextureUV();
    
  private:
    // disabled
    VertexBufferGPU_PositionTextureUV(const VertexBufferGPU_PositionTextureUV& cpy);
    VertexBufferGPU_PositionTextureUV& operator=( const VertexBufferGPU_PositionTextureUV& cpy);
};

#endif /* VERTEXBUFFER_GPU_POSITIONTEXTURE_UV_H */
