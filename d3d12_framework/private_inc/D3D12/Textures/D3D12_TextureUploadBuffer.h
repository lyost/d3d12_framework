#ifndef D3D12_TEXTURE_UPLOAD_BUFFER_H
#define D3D12_TEXTURE_UPLOAD_BUFFER_H

#include <d3d12.h>
#include "Graphics/Textures/TextureUploadBuffer.h"

class D3D12_TextureUploadBuffer : public TextureUploadBuffer
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
    static TextureUploadBuffer* Create(const GraphicsCore& graphics, const Texture1D& texture);

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
    static TextureUploadBuffer* Create(const GraphicsCore& graphics, const Texture2D& texture);

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
    static TextureUploadBuffer* Create(const GraphicsCore& graphics, const Texture3D& texture);

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
    static TextureUploadBuffer* Create(const GraphicsCore& graphics, const Texture1DArray& texture);

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
    static TextureUploadBuffer* Create(const GraphicsCore& graphics, const Texture2DArray& texture);

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
    static TextureUploadBuffer* Create(const GraphicsCore& graphics, const TextureCube& texture);

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
    static TextureUploadBuffer* Create(const GraphicsCore& graphics, const TextureCubeArray& texture);

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
    /// <param name="mip_level">
    /// mipmap level to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture1D& texture, const std::vector<UINT8>& data, UINT16 mip_level);

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
    /// <param name="mip_level">
    /// mipmap level to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2D& texture, const std::vector<UINT8>& data, UINT16 mip_level);

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
    /// <param name="mip_level">
    /// mipmap level to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture3D& texture, const std::vector<UINT8>& data, UINT16 mip_level);

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
    /// <param name="mip_level">
    /// mipmap level to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture1DArray& texture, UINT16 index, const std::vector<UINT8>& data, UINT16 mip_level);

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
    /// <param name="mip_level">
    /// mipmap level to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, Texture2DArray& texture, UINT16 index, const std::vector<UINT8>& data, UINT16 mip_level);

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
    /// <param name="mip_level">
    /// mipmap level to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, TextureCube& texture, UINT16 index, const std::vector<UINT8>& data, UINT16 mip_level);

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
    /// <param name="mip_level">
    /// mipmap level to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUpload(GraphicsCore& graphics, CommandList& command_list, TextureCubeArray& texture, UINT16 cube_index, UINT16 side_index, const std::vector<UINT8>& data, UINT16 mip_level);

  protected:
    D3D12_TextureUploadBuffer(ID3D12Resource* buffer);

  private:
    // disabled
    D3D12_TextureUploadBuffer();
    D3D12_TextureUploadBuffer(const D3D12_TextureUploadBuffer& cpy);
    D3D12_TextureUploadBuffer& operator=(const D3D12_TextureUploadBuffer& cpy);

    /// <summary>
    /// Main implementation of the various public Create functions that handles 1D, 2D, and 3D textures and texture arrays
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="resource_desc">
    /// resource description of the texture to create an upload buffer for
    /// </param>
    static TextureUploadBuffer* CreateInternal(const GraphicsCore& graphics, D3D12_RESOURCE_DESC resource_desc);

    /// <summary>
    /// Main implementation of the various public PrepUpload functions that handles 1D, 2D, and 3D textures and texture arrays
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
    /// subresource index to upload to
    /// </param>
    /// <param name="data">
    /// bytes to write to the texture
    /// </param>
    /// <param name="mip_level">
    /// mipmap level to upload to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void PrepUploadInternal(GraphicsCore& graphics, CommandList& command_list, ID3D12Resource* texture, UINT index, const std::vector<UINT8>& data);

    /// <summary>
    /// D3D12 buffer resource
    /// </summary>
    ID3D12Resource* m_buffer;
};

#endif /* D3D12_TEXTURE_UPLOAD_BUFFER_H */
