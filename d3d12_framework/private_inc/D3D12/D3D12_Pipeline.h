#ifndef D3D12_PIPELINE_H
#define D3D12_PIPELINE_H

#include <d3d12.h>
#include "Graphics/Pipeline.h"

/// <summary>
/// Collection of settings for the graphics pipeline
/// </summary>
class D3D12_Pipeline : public Pipeline
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
    static D3D12_Pipeline* Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& pixel_shader,
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
    static D3D12_Pipeline* Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& pixel_shader, DepthFuncs depth_func,
      const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig);
    
    ~D3D12_Pipeline();

    ID3D12PipelineState* GetPipeline() const;
    
  private:
    D3D12_Pipeline(ID3D12PipelineState* pipeline);

    // disabled
    D3D12_Pipeline();
    D3D12_Pipeline(const D3D12_Pipeline& cpy);
    D3D12_Pipeline& operator=(const D3D12_Pipeline& cpy);

    /// <summary>
    /// pipeline state object that matches the configuration specified when the instance was created
    /// </summary>
    ID3D12PipelineState* m_pipeline;
};

#endif /* D3D12_PIPELINE_H */
