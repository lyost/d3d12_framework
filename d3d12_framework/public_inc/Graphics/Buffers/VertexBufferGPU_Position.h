#ifndef VERTEXBUFFER_GPU_POSITION_H
#define VERTEXBUFFER_GPU_POSITION_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"

/// <summary>
/// Vertex buffer whose only element is position
/// </summary>
class VertexBufferGPU_Position : public VertexBuffer
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
    static VertexBufferGPU_Position* CreateD3D12(GraphicsCore& graphics, UINT num);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBufferGPU_Position();

  protected:
    VertexBufferGPU_Position();
    
  private:
    // disabled
    VertexBufferGPU_Position(const VertexBufferGPU_Position& cpy);
    VertexBufferGPU_Position& operator=( const VertexBufferGPU_Position& cpy);
};

#endif /* VERTEXBUFFER_GPU_POSITION_H */
