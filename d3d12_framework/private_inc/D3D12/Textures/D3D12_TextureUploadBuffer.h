#ifndef D3D12_TEXTURE_UPLOAD_BUFFER_H
#define D3D12_TEXTURE_UPLOAD_BUFFER_H

#include <d3d12.h>
#include "Graphics/Textures/TextureUploadBuffer.h"

class D3D12_TextureUploadBuffer : public TextureUploadBuffer
{
  public:
    /// <summary>
    /// Creates D3D12 buffers for uploading textures
    /// </summary>
    /// <param name="graphics">
    /// Core graphics interface
    /// </param>
    /// <param name="textures">
    /// Textures to create the upload buffer for
    /// </param>
    /// <param name="out">
    /// Where to put the created upload buffers.  They will be added to the end of the array.
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static void Create(const GraphicsCore& graphics, const std::vector<Texture*>& textures, std::vector<TextureUploadBuffer*>& out);

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
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture1D& texture, const std::vector<UINT8>& data);

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
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2D& texture, const std::vector<UINT8>& data);

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
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture3D& texture, const std::vector<UINT8>& data);

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
    /// <param name="index">
    /// index of the texture in the array to upload to
    /// </param>
    /// <param name="data">
    /// bytes to write to the texture
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture1DArray& texture, UINT16 index, const std::vector<UINT8>& data);

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
    /// <param name="index">
    /// index of the texture in the array to upload to
    /// </param>
    /// <param name="data">
    /// bytes to write to the texture
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2DArray& texture, UINT16 index, const std::vector<UINT8>& data);

  protected:
    D3D12_TextureUploadBuffer(ID3D12Resource* buffer);

  private:
    // disabled
    D3D12_TextureUploadBuffer();
    D3D12_TextureUploadBuffer(const D3D12_TextureUploadBuffer& cpy);
    D3D12_TextureUploadBuffer& operator=(const D3D12_TextureUploadBuffer& cpy);

    /// <summary>
    /// Main implementation of the various public PrepUpload functions that handles 1D, 2D, and 3D textures
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
    /// <param name="index">
    /// index of the texture in the array to upload to
    /// </param>
    /// <param name="data">
    /// bytes to write to the texture
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUploadInternal(GraphicsCore& graphics, CommandList& command_list, ID3D12Resource* texture, UINT16 index, const std::vector<UINT8>& data);

    /// <summary>
    /// D3D12 buffer resource
    /// </summary>
    ID3D12Resource* m_buffer;
};

#endif /* D3D12_TEXTURE_UPLOAD_BUFFER_H */
