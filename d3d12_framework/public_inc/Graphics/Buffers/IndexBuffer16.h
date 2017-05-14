#ifndef INDEX_BUFFER16_H
#define INDEX_BUFFER16_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Buffers/IndexBufferGPU16.h"

/// <summary>
/// Index buffer with 16bit entries
/// </summary>
class IndexBuffer16 : public IndexBuffer
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
    /// <param name="data">
    /// initial data for the index buffer
    /// </param>
    /// <returns>
    /// pointer to the index buffer instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static IndexBuffer16* CreateD3D12(GraphicsCore& graphics, UINT num, const WORD* data);
    
    /// <summary>
    /// Cleans up the index buffer
    /// </summary>
    virtual ~IndexBuffer16();

    /// <summary>
    /// Preps the command list for uploading the contents of the index buffer to the specified GPU-only accessible index buffer.  The command list must execute followed by a fence for the transfer to be
    /// completed.
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="command_list">
    /// command list to use for uploading
    /// </param>
    /// <param name="buffer">
    /// GPU-only index buffer to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, const IndexBufferGPU16& buffer) = 0;
    
  protected:
    IndexBuffer16();
    
  private:
    // disabled
    IndexBuffer16(const IndexBuffer16& cpy);
    IndexBuffer16& operator=(const IndexBuffer16& cpy);
};

#endif /* INDEX+BUFFER16_H */
