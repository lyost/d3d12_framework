#ifndef PIPELINE_H
#define PIPELINE_H

class GraphicsCore;

#include "Graphics/GraphicsCore.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Topology.h"
#include "Graphics/Shader.h"
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RootSignature.h"
#include "Graphics/DepthEnums.h"

/// <summary>
/// Collection of settings for the graphics pipeline
/// </summary>
class Pipeline
{
  public:
    /// <summary>
    /// Creates a graphics pipeline with the specified configuation, and with rasterizer state set to defaults, depth stencil disabled, multisampling disabled, and only the vertex and pixel shaders
    /// active
    /// </summary>
    /// <param name="graphics_core">
    /// reference to the core graphics instance
    /// </param>
    /// <param name="input_layout">
    /// input layout of the data to draw
    /// </param>
    /// <param name="topology">
    /// primitive topology for data to draw
    /// </param>
    /// <param name="vertex_shader">
    /// shader to use in the vertex shader stage
    /// </param>
    /// <param name="pixel_shader">
    /// shader to use in the pixel shader stage
    /// </param>
    /// <param name="rtv_config">
    /// configuration for the render target views
    /// </param>
    /// <param name="root_sig">
    /// root signature
    /// </param>
    /// <returns>
    /// pointer to the pipeline instance on success
    /// NULL on error
    /// </returns>
    static Pipeline* CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& pixel_shader,
      const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig);

    /// <summary>
    /// Creates a graphics pipeline with the specified configuation, and with rasterizer state set to defaults, multisampling disabled, and only the vertex and pixel shaders active
    /// </summary>
    /// <param name="graphics_core">
    /// reference to the core graphics instance
    /// </param>
    /// <param name="input_layout">
    /// input layout of the data to draw
    /// </param>
    /// <param name="topology">
    /// primitive topology for data to draw
    /// </param>
    /// <param name="vertex_shader">
    /// shader to use in the vertex shader stage
    /// </param>
    /// <param name="geometry_shader">
    /// shader to use in the geometry shader stage
    /// </param>
    /// <param name="pixel_shader">
    /// shader to use in the pixel shader stage
    /// </param>
    /// <param name="depth_func">
    /// depth comparision function to use
    /// </param>
    /// <param name="rtv_config">
    /// configuration for the render target views
    /// </param>
    /// <param name="root_sig">
    /// root signature
    /// </param>
    /// <returns>
    /// pointer to the pipeline instance on success
    /// NULL on error
    /// </returns>
    static Pipeline* CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& geometry_shader,
      const Shader& pixel_shader, DepthFuncs depth_func, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig);

    /// <summary>
    /// Creates a graphics pipeline with the specified configuation, and with rasterizer state set to defaults, multisampling disabled, and only the vertex, geometry, and pixel shaders active
    /// </summary>
    /// <param name="graphics_core">
    /// reference to the core graphics instance
    /// </param>
    /// <param name="input_layout">
    /// input layout of the data to draw
    /// </param>
    /// <param name="topology">
    /// primitive topology for data to draw
    /// </param>
    /// <param name="vertex_shader">
    /// shader to use in the vertex shader stage
    /// </param>
    /// <param name="pixel_shader">
    /// shader to use in the pixel shader stage
    /// </param>
    /// <param name="depth_func">
    /// depth comparision function to use
    /// </param>
    /// <param name="rtv_config">
    /// configuration for the render target views
    /// </param>
    /// <param name="root_sig">
    /// root signature
    /// </param>
    /// <returns>
    /// pointer to the pipeline instance on success
    /// NULL on error
    /// </returns>
    static Pipeline* CreateD3D12(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& pixel_shader, DepthFuncs depth_func,
      const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig);

    virtual ~Pipeline();

  protected:
    Pipeline();
    
  private:
    // disabled
    Pipeline(const Pipeline& cpy);
    Pipeline& operator=(const Pipeline& cpy);
};

#endif /* PIPELINE_H */
