#ifndef VERTEXBUFFER_GPU_POSITIONTEXTURE_UVW_H
#define VERTEXBUFFER_GPU_POSITIONTEXTURE_UVW_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"

/// <summary>
/// Vertex buffer whose elements are position and texture values
/// </summary>
class VertexBufferGPU_PositionTextureUVW : public VertexBuffer
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
    static VertexBufferGPU_PositionTextureUVW* CreateD3D12(GraphicsCore& graphics, UINT num);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBufferGPU_PositionTextureUVW();

  protected:
    VertexBufferGPU_PositionTextureUVW();
    
  private:
    // disabled
    VertexBufferGPU_PositionTextureUVW(const VertexBufferGPU_PositionTextureUVW& cpy);
    VertexBufferGPU_PositionTextureUVW& operator=( const VertexBufferGPU_PositionTextureUVW& cpy);
};

#endif /* VERTEXBUFFER_GPU_POSITIONTEXTURE_UVW_H */
