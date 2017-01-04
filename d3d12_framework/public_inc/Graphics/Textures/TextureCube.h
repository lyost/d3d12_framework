#ifndef TEXTURE_CUBE_H
#define TEXTURE_CUBE_H

class GraphicsCore;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"

class TextureCube
{
  public:
    /// <summary>
    /// Creates a D3D12 texture cube
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
    /// <param name="format">
    /// texture format
    /// </param>
    /// <param name="mip_levels">
    /// number of mipmap levels
    /// </param>
    /// <returns>
    /// D3D12 texture cube
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static TextureCube* CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format, UINT16 mip_levels = 1);

    virtual ~TextureCube();
    
  protected:
    TextureCube();

  private:
    // disabled
    TextureCube(const TextureCube& cpy);
    TextureCube& operator=(const TextureCube& cpy);
};

#endif /* TEXTURE_CUBE_H */
