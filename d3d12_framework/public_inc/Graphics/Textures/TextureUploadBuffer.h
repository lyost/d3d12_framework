#ifndef TEXTURE_UPLOAD_BUFFER_H
#define TEXTURE_UPLOAD_BUFFER_H

#include "Graphics/CommandList.h"
#include "Graphics/Textures/Texture1D.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/Texture3D.h"
#include "Graphics/Textures/Texture1DArray.h"
#include "Graphics/Textures/Texture2DArray.h"
#include "Graphics/Textures/TextureCube.h"
#include "Graphics/Textures/TextureCubeArray.h"

class TextureUploadBuffer
{
  public:
    /// <summary>
    /// Creates a D3D12 buffer for uploading the texture
    /// </summary>
    /// <param name="graphics">
    /// Core graphics interface
    /// </param>
    /// <param name="texture">
    /// Texture to create the upload buffer for
    /// </param>
    /// <returns>
    /// Texture upload buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureUploadBuffer* CreateD3D12(const GraphicsCore& graphics, const Texture1D& texture);

    /// <summary>
    /// Creates a D3D12 buffer for uploading the texture
    /// </summary>
    /// <param name="graphics">
    /// Core graphics interface
    /// </param>
    /// <param name="texture">
    /// Texture to create the upload buffer for
    /// </param>
    /// <returns>
    /// Texture upload buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureUploadBuffer* CreateD3D12(const GraphicsCore& graphics, const Texture2D& texture);

    /// <summary>
    /// Creates a D3D12 buffer for uploading the texture
    /// </summary>
    /// <param name="graphics">
    /// Core graphics interface
    /// </param>
    /// <param name="texture">
    /// Texture to create the upload buffer for
    /// </param>
    /// <returns>
    /// Texture upload buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureUploadBuffer* CreateD3D12(const GraphicsCore& graphics, const Texture3D& texture);

    /// <summary>
    /// Creates a D3D12 buffer for uploading a texture in the array
    /// <remarks>
    /// If you want to upload all to all the textures in the array without re-using the same buffer, then an upload buffer for each texture would need to be created
    /// </remarks>
    /// </summary>
    /// <param name="graphics">
    /// Core graphics interface
    /// </param>
    /// <param name="texture">
    /// Texture to create the upload buffer for
    /// </param>
    /// <returns>
    /// Texture upload buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureUploadBuffer* CreateD3D12(const GraphicsCore& graphics, const Texture1DArray& texture);

    /// <summary>
    /// Creates a D3D12 buffer for uploading a texture in the array
    /// <remarks>
    /// If you want to upload all to all the textures in the array without re-using the same buffer, then an upload buffer for each texture would need to be created
    /// </remarks>
    /// </summary>
    /// <param name="graphics">
    /// Core graphics interface
    /// </param>
    /// <param name="texture">
    /// Texture to create the upload buffer for
    /// </param>
    /// <returns>
    /// Texture upload buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureUploadBuffer* CreateD3D12(const GraphicsCore& graphics, const Texture2DArray& texture);

    /// <summary>
    /// Creates a D3D12 buffer for uploading the texture for a side of the cube
    /// <remarks>
    /// If you want to upload all to all the textures in the cube without re-using the same buffer, then an upload buffer for each side's texture would need to be created
    /// </remarks>
    /// </summary>
    /// <param name="graphics">
    /// Core graphics interface
    /// </param>
    /// <param name="texture">
    /// Texture to create the upload buffer for
    /// </param>
    /// <returns>
    /// Texture upload buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureUploadBuffer* CreateD3D12(const GraphicsCore& graphics, const TextureCube& texture);

    /// <summary>
    /// Creates a D3D12 buffer for uploading the texture for a side of a cube
    /// <remarks>
    /// If you want to upload all to all the textures for all the cubes without re-using the same buffer, then an upload buffer per cube and per side would need to be created
    /// </remarks>
    /// </summary>
    /// <param name="graphics">
    /// Core graphics interface
    /// </param>
    /// <param name="texture">
    /// Texture to create the upload buffer for
    /// </param>
    /// <returns>
    /// Texture upload buffer
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureUploadBuffer* CreateD3D12(const GraphicsCore& graphics, const TextureCubeArray& texture);

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
    /// index of which side of the cube to upload to
    /// </param>
    /// <param name="data">
    /// bytes to write to the texture
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, TextureCube& texture, UINT16 index, const std::vector<UINT8>& data) = 0;

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
    /// <param name="cube_index">
    /// index of which cube to upload to
    /// </param>
    /// <param name="side_index">
    /// index of which side of the cube to upload to
    /// </param>
    /// <param name="data">
    /// bytes to write to the texture
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void PrepUpload(GraphicsCore& graphics, CommandList& command_list, TextureCubeArray& texture, UINT16 cube_index, UINT16 side_index, const std::vector<UINT8>& data) = 0;

  protected:
    TextureUploadBuffer();

  private:
    // disabled
    TextureUploadBuffer(const TextureUploadBuffer& cpy);
    TextureUploadBuffer& operator=(const TextureUploadBuffer& cpy);
};

#endif /* TEXTURE_UPLOAD_BUFFER_H */
