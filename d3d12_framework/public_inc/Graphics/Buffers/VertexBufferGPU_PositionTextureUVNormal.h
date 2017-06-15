#ifndef VERTEXBUFFER_GPU_POSITION_TEXTURE_UV_NORMAL_H
#define VERTEXBUFFER_GPU_POSITION_TEXTURE_UV_NORMAL_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"

/// <summary>
/// Vertex buffer whose elements are position, texture uv coordinates, and a 3d normal vector
/// </summary>
class VertexBufferGPU_PositionTextureUVNormal : public VertexBuffer
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
    static VertexBufferGPU_PositionTextureUVNormal* CreateD3D12(GraphicsCore& graphics, UINT num);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBufferGPU_PositionTextureUVNormal();

  protected:
    VertexBufferGPU_PositionTextureUVNormal();
    
  private:
    // disabled
    VertexBufferGPU_PositionTextureUVNormal(const VertexBufferGPU_PositionTextureUVNormal& cpy);
    VertexBufferGPU_PositionTextureUVNormal& operator=( const VertexBufferGPU_PositionTextureUVNormal& cpy);
};

#endif /* VERTEXBUFFER_GPU_POSITION_TEXTURE_UV_NORMAL_H */
