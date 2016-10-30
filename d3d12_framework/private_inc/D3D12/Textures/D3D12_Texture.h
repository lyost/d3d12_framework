#ifndef D3D12_TEXTURE_H
#define D3D12_TEXTURE_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/Texture.h"

/// <summary>
/// Base class for textures
/// </summary>
class D3D12_Texture : public Texture
{
  public:
    /// <summary>
    /// Loads a texture from a file
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="path">
    /// path to the file to load
    /// </param>
    /// <returns>
    /// pointer to the texture instance on success
    /// NULL on error
    /// </returns>
    static Texture* LoadFromFile(GraphicsCore& graphics, const WCHAR* path);

    ~D3D12_Texture();

    /// <summary>
    /// Retrieves the D3D12 resource of the texture
    /// </summary>
    /// <returns>
    /// D3D12 resource for the texture
    /// </returns>
    ID3D12Resource* GetResource() const;

  protected:
    D3D12_Texture(ID3D12Resource* texture, D3D12_SHADER_RESOURCE_VIEW_DESC srv_desc);

  private:
    // disabled
    D3D12_Texture();
    D3D12_Texture(const D3D12_Texture& cpy);
    D3D12_Texture& operator=(const D3D12_Texture& cpy);

    /// <summary>
    /// loaded texture
    /// </summary>
    ID3D12Resource* m_texture;

    /// <summary>
    /// default shader resource view of m_texture
    /// </summary>
    D3D12_SHADER_RESOURCE_VIEW_DESC m_srv_desc;
};

#endif /* TEXTURE_H */
