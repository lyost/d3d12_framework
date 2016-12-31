#ifndef TEXTURE_CUBE_ARRAY_H
#define TEXTURE_CUBE_ARRAY_H

class GraphicsCore;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"

class TextureCubeArray
{
  public:
    /// <summary>
    /// Creates a D3D12 texture cube array
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="shader_buffer_heap">
    /// shader resources descriptor heap that the texture will be accessed from
    /// </param>
    /// <param name="width">
    /// width of a texture for each side of the cube in pixels
    /// </param>
    /// <param name="height">
    /// height of a texture for each side of the cube in pixels
    /// </param>
    /// <param name="num_cubes">
    /// number of cubes in the array
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// D3D12 texture cube array
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureCubeArray* CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 num_cubes, GraphicsDataFormat format);

    virtual ~TextureCubeArray();
    
  protected:
    TextureCubeArray();

  private:
    // disabled
    TextureCubeArray(const TextureCubeArray& cpy);
    TextureCubeArray& operator=(const TextureCubeArray& cpy);
};

#endif /* TEXTURE_CUBE_ARRAY_H */
