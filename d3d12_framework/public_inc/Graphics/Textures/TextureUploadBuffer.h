#ifndef TEXTURE_UPLOAD_BUFFER_H
#define TEXTURE_UPLOAD_BUFFER_H

#include <vector>
#include "Graphics/CommandList.h"
#include "Graphics/Textures/Texture.h"

class TextureUploadBuffer
{
  public:
    /// <summary>
    /// Creates D3D12 buffers for uploading textures
    /// <remarks>
    /// In order to preserve upload buffers being added to "out" in the same order as the textures are in "textures", only 1 upload buffer will be created per texture array.  If you want multiple upload
    /// buffers for a texture array, then it should be repeated in "textures".
    /// </remarks>
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
    static void CreateD3D12(const GraphicsCore& graphics, const std::vector<Texture*>& textures, std::vector<TextureUploadBuffer*>& out);

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
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture1D& texture, const std::vector<UINT8>& data) = 0;

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
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2D& texture, const std::vector<UINT8>& data) = 0;

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
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture3D& texture, const std::vector<UINT8>& data) = 0;

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
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture1DArray& texture, UINT16 index, const std::vector<UINT8>& data) = 0;

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
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2DArray& texture, UINT16 index, const std::vector<UINT8>& data) = 0;

  protected:
    TextureUploadBuffer();

  private:
    // disabled
    TextureUploadBuffer(const TextureUploadBuffer& cpy);
    TextureUploadBuffer& operator=(const TextureUploadBuffer& cpy);
};

#endif /* TEXTURE_UPLOAD_BUFFER_H */
