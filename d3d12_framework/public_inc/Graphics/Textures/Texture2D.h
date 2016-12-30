#ifndef TEXTURE2D_H
#define TEXTURE2D_H

class GraphicsCore;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"

class Texture2D
{
  public:
    /// <summary>
    /// Creates a D3D12 2D texture
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
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// D3D12 texture 2D
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture2D* CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format);

    virtual ~Texture2D();
    
  protected:
    Texture2D();

  private:
    // disabled
    Texture2D(const Texture2D& cpy);
    Texture2D& operator=(const Texture2D& cpy);
};

#endif /* TEXTURE2D_H */
