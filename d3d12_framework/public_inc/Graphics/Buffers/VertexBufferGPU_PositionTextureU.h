#ifndef VERTEXBUFFER_GPU_POSITIONTEXTURE_U_H
#define VERTEXBUFFER_GPU_POSITIONTEXTURE_U_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"

/// <summary>
/// Vertex buffer whose elements are position and texture values
/// </summary>
class VertexBufferGPU_PositionTextureU : public VertexBuffer
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
    static VertexBufferGPU_PositionTextureU* CreateD3D12(GraphicsCore& graphics, UINT num);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBufferGPU_PositionTextureU();

  protected:
    VertexBufferGPU_PositionTextureU();
    
  private:
    // disabled
    VertexBufferGPU_PositionTextureU(const VertexBufferGPU_PositionTextureU& cpy);
    VertexBufferGPU_PositionTextureU& operator=( const VertexBufferGPU_PositionTextureU& cpy);
};

#endif /* VERTEXBUFFER_GPU_POSITIONTEXTURE_U_H */
