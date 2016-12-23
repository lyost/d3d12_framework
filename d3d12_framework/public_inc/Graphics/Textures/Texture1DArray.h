#ifndef TEXTURE1D_ARRAY_H
#define TEXTURE1D_ARRAY_H

class GraphicsCore;
class TextureResourceHeap;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/TextureResourceHeap.h"
#include "Graphics/GraphicsDataFormat.h"
#include "Graphics/Textures/Texture.h"

class Texture1DArray : public Texture
{
  public:
    /// <summary>
    /// Determines the size the texture array will need to be to hold the requested number of bytes
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="length">
    /// number of textures in the array
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
    static UINT GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT16 length, GraphicsDataFormat format);

    /// <summary>
    /// Creates a D3D12 1D texture array
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
    /// <param name="length">
    /// number of textures in the array
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// D3D12 texture 1D array
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture1DArray* CreateD3D12(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT16 length, GraphicsDataFormat format);

    virtual ~Texture1DArray();

    /// <summary>
    /// Retrieves which type of texture the instance is
    /// </summary>
    /// <returns>
    /// id of the texture type
    /// </returns>
    TextureType GetType() const;
    
  protected:
    Texture1DArray();

  private:
    // disabled
    Texture1DArray(const Texture1DArray& cpy);
    Texture1DArray& operator=(const Texture1DArray& cpy);
};

#endif /* TEXTURE1D_ARRAY_H */
