#include <cassert>
#include "private_inc/D3D12/D3D12_RenderTargetViewConfig.h"
using namespace std;

D3D12_RenderTargetViewConfig::D3D12_RenderTargetViewConfig(UINT num)
:m_num(num)
{
  assert(num < MAX_RENDER_TARGETS);

  // D3D12's pipeline creation needs the blend state fields set to valid values for pipeline creation to work even if blending is disabled
  for (UINT i = 0; i < MAX_RENDER_TARGETS; i++)
  {
    D3D12_RENDER_TARGET_BLEND_DESC& blend = m_desc.RenderTarget[i];
    blend.BlendEnable                     = false;
    blend.LogicOpEnable                   = false;
    blend.LogicOp                         = D3D12_LOGIC_OP_NOOP;
    blend.SrcBlend                        = D3D12_BLEND_ONE;
    blend.DestBlend                       = D3D12_BLEND_ZERO;
    blend.BlendOp                         = D3D12_BLEND_OP_ADD;
    blend.SrcBlendAlpha                   = D3D12_BLEND_ONE;
    blend.DestBlendAlpha                  = D3D12_BLEND_ZERO;
    blend.BlendOpAlpha                    = D3D12_BLEND_OP_ADD;
    blend.RenderTargetWriteMask           = D3D12_COLOR_WRITE_ENABLE_ALL;
  }
}

D3D12_RenderTargetViewConfig::~D3D12_RenderTargetViewConfig()
{
}

void D3D12_RenderTargetViewConfig::SetAlphaToCoverageEnable(bool enable)
{
  m_desc.AlphaToCoverageEnable = enable;
}

void D3D12_RenderTargetViewConfig::SetIndependentBlendEnable(bool enable)
{
  m_desc.IndependentBlendEnable = enable;
}

void D3D12_RenderTargetViewConfig::SetFormat(UINT index, RenderTargetViewFormat format)
{
  m_formats[index] = format;
}

void D3D12_RenderTargetViewConfig::DisableBlend(UINT index)
{
  assert(index < MAX_RENDER_TARGETS);

  m_desc.RenderTarget[index].BlendEnable   = false;
}

void D3D12_RenderTargetViewConfig::EnableBlend(UINT index, bool enable_logic_op, LogicOp logic_op, BlendModes src, BlendModes dst, BlendOp blend_op, BlendModes src_alpha, BlendModes dst_alpha,
  BlendOp alpha_op, COLOR_WRITE_MODE write_mask)
{
  assert(index < m_num);

  D3D12_RENDER_TARGET_BLEND_DESC& blend = m_desc.RenderTarget[index];
  blend.BlendEnable                     = true;
  blend.LogicOpEnable                   = enable_logic_op;
  blend.LogicOp                         = (D3D12_LOGIC_OP)logic_op;
  blend.SrcBlend                        = (D3D12_BLEND)src;
  blend.DestBlend                       = (D3D12_BLEND)dst;
  blend.BlendOp                         = (D3D12_BLEND_OP)blend_op;
  blend.SrcBlendAlpha                   = (D3D12_BLEND)src_alpha;
  blend.DestBlendAlpha                  = (D3D12_BLEND)dst_alpha;
  blend.BlendOpAlpha                    = (D3D12_BLEND_OP)alpha_op;
  blend.RenderTargetWriteMask           = (UINT8)write_mask;
}

UINT D3D12_RenderTargetViewConfig::GetNumRenderTargets() const
{
  return m_num;
}

D3D12_BLEND_DESC D3D12_RenderTargetViewConfig::GetBlendState() const
{
  return m_desc;
}

const RenderTargetViewFormat* D3D12_RenderTargetViewConfig::GetFormats() const
{
  return m_formats;
}
