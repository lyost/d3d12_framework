#ifndef VERTEXBUFFER_GPU_POSITION_COLOR_H
#define VERTEXBUFFER_GPU_POSITION_COLOR_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"

/// <summary>
/// Vertex buffer whose elements are position and rgba color values
/// </summary>
class VertexBufferGPU_PositionColor : public VertexBuffer
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
    static VertexBufferGPU_PositionColor* CreateD3D12(GraphicsCore& graphics, UINT num);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBufferGPU_PositionColor();

  protected:
    VertexBufferGPU_PositionColor();
    
  private:
    // disabled
    VertexBufferGPU_PositionColor(const VertexBufferGPU_PositionColor& cpy);
    VertexBufferGPU_PositionColor& operator=( const VertexBufferGPU_PositionColor& cpy);
};

#endif /* VERTEXBUFFER_GPU_POSITION_COLOR_H */
