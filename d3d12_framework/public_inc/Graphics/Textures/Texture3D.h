#ifndef TEXTURE3D_H
#define TEXTURE3D_H

class GraphicsCore;
class TextureResourceHeap;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/TextureResourceHeap.h"
#include "Graphics/GraphicsDataFormat.h"
#include "Graphics/Textures/Texture.h"

class Texture3D : public Texture
{
  public:
    /// <summary>
    /// Determines the size a texture will need to be to hold the requested number of bytes
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="height">
    /// height of the texture in pixels
    /// </param>
    /// <param name="depth">
    /// depth of the texture in pixels
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// number of bytes the texture should be created with
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static UINT GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height, UINT16 depth, GraphicsDataFormat format);

    /// <summary>
    /// Creates a D3D12 3D texture
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="resource_heap">
    /// texture upload resource heap to put the texture into
    /// </param>
    /// <param name="shader_buffer_heap">
    /// shader resources descriptor heap that the texture will be accessed from
    /// </param>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="height">
    /// height of the texture in pixels
    /// </param>
    /// <param name="depth">
    /// depth of the texture in pixels
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// D3D12 texture 3D
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture3D* CreateD3D12(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 depth,
      GraphicsDataFormat format);

    virtual ~Texture3D();

    /// <summary>
    /// Retrieves which type of texture the instance is
    /// </summary>
    /// <returns>
    /// id of the texture type
    /// </returns>
    TextureType GetType() const;
    
  protected:
    Texture3D();

  private:
    // disabled
    Texture3D(const Texture3D& cpy);
    Texture3D& operator=(const Texture3D& cpy);
};

#endif /* TEXTURE3D_H */
