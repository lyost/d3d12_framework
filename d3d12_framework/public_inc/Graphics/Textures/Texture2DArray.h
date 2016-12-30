#ifndef TEXTURE2D_ARRAY_H
#define TEXTURE2D_ARRAY_H

class GraphicsCore;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"

class Texture2DArray
{
  public:
    /// <summary>
    /// Creates a D3D12 2D texture array
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
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
    /// <param name="length">
    /// number of textures in the array
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// D3D12 texture 2D array
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture2DArray* CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 length, GraphicsDataFormat format);

    virtual ~Texture2DArray();
    
  protected:
    Texture2DArray();

  private:
    // disabled
    Texture2DArray(const Texture2DArray& cpy);
    Texture2DArray& operator=(const Texture2DArray& cpy);
};

#endif /* TEXTURE2D_ARRAY_H */
