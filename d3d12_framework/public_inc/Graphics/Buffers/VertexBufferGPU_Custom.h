#ifndef VERTEXBUFFER_GPU_CUSTOM_H
#define VERTEXBUFFER_GPU_CUSTOM_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer.h"

/// <summary>
/// Vertex buffer whose only element is position
/// </summary>
class VertexBufferGPU_Custom : public VertexBuffer
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
    /// <param name="size">
    /// number of bytes in 1 entry
    /// </param>
    /// <returns>
    /// pointer to the vertex buffer instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static VertexBufferGPU_Custom* CreateD3D12(GraphicsCore& graphics, UINT num, UINT size);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    virtual ~VertexBufferGPU_Custom();

  protected:
    VertexBufferGPU_Custom();
    
  private:
    // disabled
    VertexBufferGPU_Custom(const VertexBufferGPU_Custom& cpy);
    VertexBufferGPU_Custom& operator=( const VertexBufferGPU_Custom& cpy);
};

#endif /* VERTEXBUFFER_GPU_CUSTOM_H */
