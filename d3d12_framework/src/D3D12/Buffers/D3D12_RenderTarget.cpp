#include "private_inc/D3D12/Buffers/D3D12_RenderTarget.h"

D3D12_RenderTarget::D3D12_RenderTarget(ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle)
:m_render_target(target),
 m_rtv_handle(handle)
{
  m_render_target->AddRef();
}

D3D12_RenderTarget::~D3D12_RenderTarget()
{
  m_render_target->Release();
}

ID3D12Resource* D3D12_RenderTarget::GetResource() const
{
  return m_render_target;
}

const D3D12_CPU_DESCRIPTOR_HANDLE& D3D12_RenderTarget::GetHandle() const
{
  return m_rtv_handle;
}
