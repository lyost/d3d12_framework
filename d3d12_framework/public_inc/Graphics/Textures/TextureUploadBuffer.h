#ifndef TEXTURE_UPLOAD_BUFFER_H
#define TEXTURE_UPLOAD_BUFFER_H

#include <vector>
#include "Graphics/CommandList.h"
#include "Graphics/Textures/Texture.h"
#include "Graphics/BufferResourceHeap.h"

class TextureUploadBuffer
{
  public:
    /// <summary>
    /// Creates a D3D12 buffer for uploading textures
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="texture">
    /// texture to create the upload buffer for
    /// </param>
    /// <param name="resource_heap">
    /// resource heap to put the upload buffer's memory into
    /// <remarks>
    /// It is the caller's responsibility to make sure there is enough room in the heap for the new buffer
    /// </remarks>
    /// </param>
    /// <returns>
    /// D3D12 texture upload buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureUploadBuffer* CreateD3D12(const GraphicsCore& graphics, const Texture& texture, BufferResourceHeap& resource_heap);

    virtual ~TextureUploadBuffer();

    /// <summary>
    /// Preps the command list for uploading the specified data to the specified texture.  The command list must execute followed by a fence for the transfer to be completed.
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="command_list">
    /// command list to use for uploading
    /// </param>
    /// <param name="texture">
    /// texture to upload to
    /// </param>
    /// <param name="data">
    /// bytes to write to the texture
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture& texture, const std::vector<UINT8>& data) = 0;

  protected:
    TextureUploadBuffer();

  private:
    // disabled
    TextureUploadBuffer(const TextureUploadBuffer& cpy);
    TextureUploadBuffer& operator=(const TextureUploadBuffer& cpy);
};

#endif /* TEXTURE_UPLOAD_BUFFER_H */
