#include "private_inc/D3D12/D3D12_Pipeline.h"
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_InputLayout.h"
#include "private_inc/D3D12/D3D12_Shader.h"
#include "private_inc/D3D12/D3D12_RenderTargetViewConfig.h"
#include "private_inc/D3D12/D3D12_RootSignature.h"
#include "log.h"
#include <sstream>

#if 0 /* old debug code, keeping around just in case it is needed again */
void dump_pso_desc(const D3D12_GRAPHICS_PIPELINE_STATE_DESC& desc)
{
  std::ostringstream out;
  out << "root sig: " << desc.pRootSignature << '\n'
    << "vs:       " << desc.VS.BytecodeLength << ' ' << desc.VS.pShaderBytecode << '\n'
    << "ps:       " << desc.PS.BytecodeLength << ' ' << desc.PS.pShaderBytecode << '\n'
    << "ds:       " << desc.DS.BytecodeLength << ' ' << desc.DS.pShaderBytecode << '\n'
    << "hs:       " << desc.HS.BytecodeLength << ' ' << desc.HS.pShaderBytecode << '\n'
    << "gs:       " << desc.GS.BytecodeLength << ' ' << desc.GS.pShaderBytecode << '\n'
    << "so:       " << desc.StreamOutput.NumEntries << ' ' << desc.StreamOutput.NumStrides << ' ' << desc.StreamOutput.pBufferStrides << ' ' << desc.StreamOutput.pSODeclaration << ' '
    << desc.StreamOutput.RasterizedStream << '\n'
    << "blend:    " << desc.BlendState.AlphaToCoverageEnable << desc.BlendState.IndependentBlendEnable << '\n';
  for (int i = 0; i < 8; i++)
  {
    const D3D12_RENDER_TARGET_BLEND_DESC& blend = desc.BlendState.RenderTarget[i];
    out << "blend[" << i << "]: " << blend.BlendEnable << ' ' << blend.LogicOpEnable << ' ' << blend.SrcBlend << ' ' << blend.DestBlend << ' ' << blend.BlendOp << ' ' << blend.SrcBlendAlpha << ' '
      << blend.DestBlendAlpha << ' ' << blend.BlendOpAlpha << ' ' << blend.LogicOp << ' ' << (UINT)blend.RenderTargetWriteMask << '\n';
  }
  out << "smask:    " << desc.SampleMask << '\n'
    << "rstate:   " << desc.RasterizerState.FillMode << ' ' << desc.RasterizerState.CullMode << ' ' << desc.RasterizerState.FrontCounterClockwise << ' ' << desc.RasterizerState.DepthBias << ' '
    << desc.RasterizerState.DepthBiasClamp << ' ' << desc.RasterizerState.SlopeScaledDepthBias << ' ' << desc.RasterizerState.DepthClipEnable << ' ' << desc.RasterizerState.MultisampleEnable << ' '
    << desc.RasterizerState.AntialiasedLineEnable << ' ' << desc.RasterizerState.ForcedSampleCount << ' ' << desc.RasterizerState.ConservativeRaster << '\n'
    << "dstate:   " << desc.DepthStencilState.DepthEnable << ' ' << desc.DepthStencilState.DepthWriteMask << ' ' << desc.DepthStencilState.DepthFunc << ' ' << desc.DepthStencilState.StencilEnable
    << ' ' << (UINT)desc.DepthStencilState.StencilReadMask << ' ' << (UINT)desc.DepthStencilState.StencilWriteMask << ' ' << desc.DepthStencilState.FrontFace.StencilFailOp << ' '
    << desc.DepthStencilState.FrontFace.StencilDepthFailOp << ' ' << desc.DepthStencilState.FrontFace.StencilPassOp << ' ' << desc.DepthStencilState.FrontFace.StencilFunc << ' '
    << desc.DepthStencilState.BackFace.StencilFailOp << ' ' << desc.DepthStencilState.BackFace.StencilDepthFailOp << ' ' << desc.DepthStencilState.BackFace.StencilPassOp << ' '
    << desc.DepthStencilState.BackFace.StencilFunc << '\n'
    << "layouts:  " << desc.InputLayout.NumElements << '\n';
  for (UINT j = 0; j < desc.InputLayout.NumElements; j++)
  {
    const D3D12_INPUT_ELEMENT_DESC& layout = desc.InputLayout.pInputElementDescs[j];
    out << "layout[" << j << "] " << layout.SemanticName << ' ' << layout.SemanticIndex << ' ' << layout.Format << ' ' << layout.InputSlot << ' ' << layout.AlignedByteOffset << ' '
      << layout.InputSlotClass << ' ' << layout.InstanceDataStepRate << '\n';
  }
  out << "ib strip: " << desc.IBStripCutValue << '\n'
    << "topology: " << desc.PrimitiveTopologyType << '\n'
    << "targets:  " << desc.NumRenderTargets << '\n';
  for (int i = 0; i < 8; i++)
  {
    out << "rtv[" << i << "]:   " << desc.RTVFormats[i] << '\n';
  }
  out << "dsv:      " << desc.DSVFormat << '\n'
    << "sample:   " << desc.SampleDesc.Count << ' ' << desc.SampleDesc.Quality << '\n'
    << "node:     " << desc.NodeMask << '\n'
    << "flags:    " << desc.Flags << '\n'
    << "cache:    " << desc.CachedPSO.pCachedBlob << ' ' << desc.CachedPSO.CachedBlobSizeInBytes << '\n';

  OutputDebugStringA(out.str().c_str());
}
#endif /* 0 */

D3D12_Pipeline* D3D12_Pipeline::Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& pixel_shader,
  const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig)
{
  const D3D12_Core&                   core   = (const D3D12_Core&)graphics_core;
  const D3D12_InputLayout&            layout = (const D3D12_InputLayout&)input_layout;
  const D3D12_Shader&                 vs     = (const D3D12_Shader&)vertex_shader;
  const D3D12_Shader&                 ps     = (const D3D12_Shader&)pixel_shader;
  const D3D12_RenderTargetViewConfig& rtv    = (const D3D12_RenderTargetViewConfig&)rtv_config;
  const D3D12_RootSignature&          root   = (const D3D12_RootSignature&)root_sig;

  D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
  desc.pRootSignature = root.GetRootSignature();
  desc.InputLayout.pInputElementDescs = layout.GetLayout();
  desc.InputLayout.NumElements = layout.GetNum();
  desc.VS = vs.GetShader();
  desc.PS = ps.GetShader();
  desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
  desc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
  desc.RasterizerState.FrontCounterClockwise = false;
  desc.RasterizerState.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
  desc.RasterizerState.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
  desc.RasterizerState.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
  desc.RasterizerState.DepthClipEnable = true;
  desc.RasterizerState.MultisampleEnable = false;
  desc.RasterizerState.AntialiasedLineEnable = false;
  desc.RasterizerState.ForcedSampleCount = 0;
  desc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
  desc.BlendState = rtv.GetBlendState();
  desc.DepthStencilState.DepthEnable = false;
  desc.DepthStencilState.StencilEnable = false;
  desc.SampleMask = UINT_MAX;
  desc.PrimitiveTopologyType = (D3D12_PRIMITIVE_TOPOLOGY_TYPE)topology;
  desc.NumRenderTargets = rtv.GetNumRenderTargets();
  memcpy(desc.RTVFormats, rtv.GetFormats(), sizeof(RenderTargetViewFormat) * desc.NumRenderTargets);
  desc.SampleDesc.Count = 1;
  desc.SampleDesc.Quality = 0;

  ID3D12PipelineState* pipeline = NULL;
  HRESULT rc = core.GetDevice()->CreateGraphicsPipelineState(&desc, __uuidof(ID3D12PipelineState), (void**)&pipeline);
  if (FAILED(rc))
  {
    log_print("Failed to create pipeline state\n");
    return NULL;
  }

  return new D3D12_Pipeline(pipeline);
}

D3D12_Pipeline* D3D12_Pipeline::Create(const GraphicsCore& graphics_core, const InputLayout& input_layout, Topology topology, const Shader& vertex_shader, const Shader& pixel_shader,
  DepthFuncs depth_func, const RenderTargetViewConfig& rtv_config, const RootSignature& root_sig)
{
  const D3D12_Core&                   core = (const D3D12_Core&)graphics_core;
  const D3D12_InputLayout&            layout = (const D3D12_InputLayout&)input_layout;
  const D3D12_Shader&                 vs = (const D3D12_Shader&)vertex_shader;
  const D3D12_Shader&                 ps = (const D3D12_Shader&)pixel_shader;
  const D3D12_RenderTargetViewConfig& rtv = (const D3D12_RenderTargetViewConfig&)rtv_config;
  const D3D12_RootSignature&          root = (const D3D12_RootSignature&)root_sig;

  D3D12_GRAPHICS_PIPELINE_STATE_DESC desc = {};
  desc.pRootSignature = root.GetRootSignature();
  desc.InputLayout.pInputElementDescs = layout.GetLayout();
  desc.InputLayout.NumElements = layout.GetNum();
  desc.VS = vs.GetShader();
  desc.PS = ps.GetShader();
  desc.RasterizerState.FillMode = D3D12_FILL_MODE_SOLID;
  desc.RasterizerState.CullMode = D3D12_CULL_MODE_BACK;
  desc.RasterizerState.FrontCounterClockwise = false;
  desc.RasterizerState.DepthBias = D3D12_DEFAULT_DEPTH_BIAS;
  desc.RasterizerState.DepthBiasClamp = D3D12_DEFAULT_DEPTH_BIAS_CLAMP;
  desc.RasterizerState.SlopeScaledDepthBias = D3D12_DEFAULT_SLOPE_SCALED_DEPTH_BIAS;
  desc.RasterizerState.DepthClipEnable = true;
  desc.RasterizerState.MultisampleEnable = false;
  desc.RasterizerState.AntialiasedLineEnable = false;
  desc.RasterizerState.ForcedSampleCount = 0;
  desc.RasterizerState.ConservativeRaster = D3D12_CONSERVATIVE_RASTERIZATION_MODE_OFF;
  desc.BlendState = rtv.GetBlendState();
  desc.DepthStencilState.DepthEnable = true;
  desc.DepthStencilState.DepthWriteMask = D3D12_DEPTH_WRITE_MASK_ALL;
  desc.DepthStencilState.DepthFunc = (D3D12_COMPARISON_FUNC)depth_func;
  desc.DepthStencilState.StencilEnable = false;
  desc.DSVFormat = DXGI_FORMAT_D32_FLOAT; // todo: make configurable?
  desc.SampleMask = UINT_MAX;
  desc.PrimitiveTopologyType = (D3D12_PRIMITIVE_TOPOLOGY_TYPE)topology;
  desc.NumRenderTargets = rtv.GetNumRenderTargets();
  memcpy(desc.RTVFormats, rtv.GetFormats(), sizeof(RenderTargetViewFormat) * desc.NumRenderTargets);
  desc.SampleDesc.Count = 1;
  desc.SampleDesc.Quality = 0;

  ID3D12PipelineState* pipeline = NULL;
  HRESULT rc = core.GetDevice()->CreateGraphicsPipelineState(&desc, __uuidof(ID3D12PipelineState), (void**)&pipeline);
  if (FAILED(rc))
  {
    log_print("Failed to create pipeline state\n");
    return NULL;
  }

  return new D3D12_Pipeline(pipeline);
}

D3D12_Pipeline::D3D12_Pipeline(ID3D12PipelineState* pipeline)
:m_pipeline(pipeline)
{
}

D3D12_Pipeline::~D3D12_Pipeline()
{
  m_pipeline->Release();
}

ID3D12PipelineState* D3D12_Pipeline::GetPipeline() const
{
  return m_pipeline;
}
