#ifndef RENDER_TARGET_VIEW_CONFIG_H
#define RENDER_TARGET_VIEW_CONFIG_H

#include <Windows.h>
#include "Graphics/RenderTargetViewFormats.h"
#include "Graphics/BlendEnums.h"
#include "Graphics/LogicOp.h"

/// <summary>
/// Configuration for a render target view when creating a Pipeline.
/// </summary>
/// <remarks>
/// Since these are used to create Pipeline instances, any changes will need the creation of a new Pipeline instance and for that Pipeline to be used in order for the changes to take effect.
/// </remarks>
class RenderTargetViewConfig
{
  public:
    /// <summary>
    /// Creates a RenderTargetViewConfig with the specified number of entries, each of which can be configured via the modifier member functions
    /// </summary>
    /// <param name="num">
    /// number of elements that make up the render target view
    /// </param>
    /// <returns>
    /// pointer to the input layout instance on success
    /// </returns>
    static RenderTargetViewConfig* CreateD3D12(UINT num);

    virtual ~RenderTargetViewConfig();

    /// <summary>
    /// Sets whether alpha-to-coverage should be enabled (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205072%28v=vs.85%29.aspx#Alpha_To_Coverage)
    /// </summary>
    /// <param name="enable">
    /// true  to enable alpha-to-coverage
    /// false otherwise
    /// </param>
    virtual void SetAlphaToCoverageEnable(bool enable) = 0;

    /// <summary>
    /// Sets whether each render target view configuartion should have its blend configuration used, or if just the first render target view's blend configuration should be used
    /// </summary>
    /// <param name="enable">
    /// true  for each render target view configuration to have its blend configuration used
    /// false for just the first render target view configuration blend configuration to be used for all render target views
    /// </param>
    virtual void SetIndependentBlendEnable(bool enable) = 0;
    
    /// <summary>
    /// Sets the format of the specified entry's render target view
    /// </summary>
    /// <param name="index">
    /// index of the render target view to set the configuration of, must be in the range [0,MAX_RENDER_TARGETS]
    /// </param>
    /// <param name="format">
    /// byte format of the render target view
    /// </param>
    virtual void SetFormat(UINT index, RenderTargetViewFormat format) = 0;

    /// <summary>
    /// Disables blending for the specified entry's render target view
    /// </summary>
    /// <param name="index">
    /// index of the render target view to set the configuration of, must be in the range [0,MAX_RENDER_TARGETS]
    /// </param>
    virtual void DisableBlend(UINT index) = 0;

    /// <summary>
    /// Enables blending for the specified entry's render target view with the associated configuration
    /// </summary>
    /// <param name="index">
    /// index of the render target view to set the configuration of, must be in the range [0,MAX_RENDER_TARGETS]
    /// </param>
    /// <param name="enable_logic_op">
    /// true  to enable logic operation
    /// false otherwise
    /// </param>
    /// <param name="logic_op">
    /// logic operation to use
    /// </param>
    /// <param name="src">
    /// blend mode to use on the RGB portion of the pixel shader output
    /// </param>
    /// <param name="dst">
    /// blend mode to use on the RGB portion of the currently in the render target
    /// </param>
    /// <param name="blend_op">
    /// how to combine src and dst
    /// </param>
    /// <param name="src_alpha">
    /// blend mode to use on the alpha portion of the pixel shader output
    /// </param>
    /// <param name="dst_alpha">
    /// blend mode to use on the alpha portion of the currently in the render target
    /// </param>
    /// <param name="alpha_op">
    /// how to combine src_alpha and dst_alpha
    /// </param>
    /// <param name="write_mask">
    /// bitwise or'ing of COLOR_WRITE_MODE values for which parts of the color are writable when blending
    /// </param>
    virtual void EnableBlend(UINT index, bool enable_logic_op, LogicOp logic_op, BlendModes src, BlendModes dst, BlendOp blend_op, BlendModes src_alpha, BlendModes dst_alpha , BlendOp alpha_op,
      COLOR_WRITE_MODE write_mask) = 0;

  protected:
    RenderTargetViewConfig();
    
  private:
    // disabled
    RenderTargetViewConfig(const RenderTargetViewConfig& cpy);
    RenderTargetViewConfig& operator=(const RenderTargetViewConfig& cpy);
};

#endif /* RENDER_TARGET_VIEW_CONFIG_H */
