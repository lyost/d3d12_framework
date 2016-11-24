#ifndef D3D12_RENDER_TARGET_VIEW_CONFIG_H
#define D3D12_RENDER_TARGET_VIEW_CONFIG_H

#include <d3d12.h>
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RenderTargetViewFormats.h"
#include "private_inc/D3D12/D3D12_Limits.h"

/// <summary>
/// Configuration for a render target view when creating a Pipeline.
/// </summary>
/// <remarks>
/// Since these are used to create Pipeline instances, any changes will need the creation of a new Pipeline instance and for that Pipeline to be used in order for the changes to take effect.
/// </remarks>
class D3D12_RenderTargetViewConfig : public RenderTargetViewConfig
{
  public:
    /// <summary>
    /// Creates a render target view config that supports [0,num) render targets, each of which can be configured via the modifier member functions
    /// </summary>
    /// <param name="num">
    /// number of elements that make up the render target view
    /// </param>
    D3D12_RenderTargetViewConfig(UINT num);
    
    ~D3D12_RenderTargetViewConfig();

    /// <summary>
    /// Sets whether alpha-to-coverage should be enabled (see https://msdn.microsoft.com/en-us/library/windows/desktop/bb205072%28v=vs.85%29.aspx#Alpha_To_Coverage)
    /// </summary>
    /// <param name="enable">
    /// true  to enable alpha-to-coverage
    /// false otherwise
    /// </param>
    void SetAlphaToCoverageEnable(bool enable);

    /// <summary>
    /// Sets whether each render target view configuartion should have its blend configuration used, or if just the first render target view's blend configuration should be used
    /// </summary>
    /// <param name="enable">
    /// true  for each render target view configuration to have its blend configuration used
    /// false for just the first render target view configuration blend configuration to be used for all render target views
    /// </param>
    void SetIndependentBlendEnable(bool enable);

    /// <summary>
    /// Sets the format of the specified entry's render target view
    /// </summary>
    /// <param name="index">
    /// index of the render target view to set the configuration of, must be in the range [0,MAX_RENDER_TARGETS]
    /// </param>
    /// <param name="format">
    /// byte format of the render target view
    /// </param>
    void SetFormat(UINT index, RenderTargetViewFormat format);

    /// <summary>
    /// Disables blending for the specified entry's render target view
    /// </summary>
    /// <param name="index">
    /// index of the render target view to set the configuration of, must be in the range [0,MAX_RENDER_TARGETS]
    /// </param>
    void DisableBlend(UINT index);

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
    void EnableBlend(UINT index, bool enable_logic_op, LogicOp logic_op, BlendModes src, BlendModes dst, BlendOp blend_op, BlendModes src_alpha, BlendModes dst_alpha, BlendOp alpha_op,
      COLOR_WRITE_MODE write_mask);

    /// <summary>
    /// Retrieves number of supported render targets
    /// </summary>
    /// <returns>
    /// true  enable alpha-to-coverage
    /// false otherwise
    /// </returns>
    UINT GetNumRenderTargets() const;

    /// <summary>
    /// Retrieves the D3D12 blend state settings
    /// </summary>
    /// <returns>
    /// blend states in the D3D12 struct
    /// </returns>
    D3D12_BLEND_DESC GetBlendState() const;

    /// <summary>
    /// Retrieves an array of the formats of the render target views
    /// </summary>
    /// <returns>
    /// array of render target formats
    /// </returns>
    const RenderTargetViewFormat* GetFormats() const;
    
  private:
    // disabled
    D3D12_RenderTargetViewConfig();
    D3D12_RenderTargetViewConfig(const D3D12_RenderTargetViewConfig& cpy);
    D3D12_RenderTargetViewConfig& operator=(const D3D12_RenderTargetViewConfig& cpy);

    /// <summary>
    /// number of render target views to configure
    /// </summary>
    UINT m_num;

    /// <summary>
    /// formats for each of the D3D12 supported render target to the output-merger stage
    /// </summary>
    RenderTargetViewFormat m_formats[MAX_RENDER_TARGETS];

    /// <summary>
    /// D3D12 blend configuration for the render target views
    /// </summary>
    D3D12_BLEND_DESC m_desc;
};

#endif /* D3D12_RENDER_TARGET_VIEW_CONFIG_H */
