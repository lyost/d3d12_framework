#ifndef TEXTURE1D_H
#define TEXTURE1D_H

class GraphicsCore;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"

class Texture1D
{
  public:
    /// <summary>
    /// Creates a D3D12 1D texture
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
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// D3D12 texture 1D
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture1D* CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, GraphicsDataFormat format);

    virtual ~Texture1D();
    
  protected:
    Texture1D();

  private:
    // disabled
    Texture1D(const Texture1D& cpy);
    Texture1D& operator=(const Texture1D& cpy);
};

#endif /* TEXTURE1D_H */
