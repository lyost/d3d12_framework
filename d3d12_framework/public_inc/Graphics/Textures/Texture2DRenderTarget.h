#ifndef TEXTURE_2D_RENDER_TARGET_H
#define TEXTURE_2D_RENDER_TARGET_H

class GraphicsCore;
class ShaderResourceDescHeap;

#include "Graphics/GraphicsCore.h"
#include "Graphics/GraphicsDataFormat.h"

/// <summary>
/// Base class for 2D textures that can also be render targets
/// <remarks>
/// By default, the resource's state is for that of a texture.  Before using it as a render target the command list that is used for rendering should have TextureToRenderTarget called with the texture
/// instance.  Correspondingly when it should be available for use as a texture, the command list's RenderTargetToTexture should be called with the corresponding render target instance.
/// See the render_target_to_texture_same_resource test program's GameMain::DrawRTV for an example of this.
/// </remarks>
/// </summary>
class Texture2DRenderTarget
{
  public:
    /// <summary>
    /// Creates a D3D12 2D texture that can be used as a render target
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
    static Texture2DRenderTarget* CreateD3D12(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, GraphicsDataFormat format);

    virtual ~Texture2DRenderTarget();
    
  protected:
    Texture2DRenderTarget();

  private:
    // disabled
    Texture2DRenderTarget(const Texture2DRenderTarget& cpy);
    Texture2DRenderTarget& operator=(const Texture2DRenderTarget& cpy);
};

#endif /* TEXTURE_2D_RENDER_TARGET_H */
