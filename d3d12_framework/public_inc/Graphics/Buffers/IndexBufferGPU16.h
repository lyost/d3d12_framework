#ifndef INDEX_BUFFER_GPU_16_H
#define INDEX_BUFFER_GPU_16_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer.h"

/// <summary>
/// Index buffer with 16bit entries that is only accessible on the GPU
/// </summary>
class IndexBufferGPU16 : public IndexBuffer
{
  public:
    /// <summary>
    /// Creates an index buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <returns>
    /// pointer to the index buffer instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static IndexBufferGPU16* CreateD3D12(GraphicsCore& graphics, UINT num);
    
    /// <summary>
    /// Cleans up the index buffer
    /// </summary>
    virtual ~IndexBufferGPU16();
    
  protected:
    IndexBufferGPU16();
    
  private:
    // disabled
    IndexBufferGPU16(const IndexBufferGPU16& cpy);
    IndexBufferGPU16& operator=(const IndexBufferGPU16& cpy);
};

#endif /* INDEX+BUFFER_GPU_16_H */
