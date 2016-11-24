#ifndef D3D12_TEXTURE_UPLOAD_BUFFER_H
#define D3D12_TEXTURE_UPLOAD_BUFFER_H

#include <d3d12.h>
#include "Graphics/Textures/TextureUploadBuffer.h"

class D3D12_TextureUploadBuffer : public TextureUploadBuffer
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
    static D3D12_TextureUploadBuffer* Create(const GraphicsCore& graphics, const Texture& texture, BufferResourceHeap& resource_heap);

    ~D3D12_TextureUploadBuffer();

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
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture& texture, const std::vector<UINT8>& data);

  protected:
    D3D12_TextureUploadBuffer(ID3D12Resource* buffer);

  private:
    // disabled
    D3D12_TextureUploadBuffer();
    D3D12_TextureUploadBuffer(const D3D12_TextureUploadBuffer& cpy);
    D3D12_TextureUploadBuffer& operator=(const D3D12_TextureUploadBuffer& cpy);

    /// <summary>
    /// D3D12 buffer resource
    /// </summary>
    ID3D12Resource* m_buffer;
};

#endif /* D3D12_TEXTURE_UPLOAD_BUFFER_H */
