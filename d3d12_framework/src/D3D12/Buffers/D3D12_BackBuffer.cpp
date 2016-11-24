#include <sstream>
#include "private_inc/D3D12/Buffers/D3D12_BackBuffer.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

const UINT NumRenderTargets = 2;

D3D12_BackBuffers* D3D12_BackBuffers::Create(ID3D12Device* device, IDXGISwapChain3* swap_chain)
{
  D3D12_DESCRIPTOR_HEAP_DESC rtv_heap_desc = {};
  rtv_heap_desc.NumDescriptors = NumRenderTargets;
  rtv_heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
  rtv_heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
  ID3D12DescriptorHeap* render_target_view = NULL;
  HRESULT rc = device->CreateDescriptorHeap(&rtv_heap_desc, __uuidof(ID3D12DescriptorHeap), (void**)&render_target_view);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create render target view heap.  HRESULT = " << rc;
    throw new FrameworkException(out.str());
  }

  UINT rtv_desc_size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

  D3D12_BackBuffers* back_buffer = new D3D12_BackBuffers(NumRenderTargets, render_target_view, swap_chain);

  D3D12_CPU_DESCRIPTOR_HANDLE rtv_handle = render_target_view->GetCPUDescriptorHandleForHeapStart();
  for (UINT i = 0; i < NumRenderTargets; i++)
  {
    ID3D12Resource* back_tmp = NULL;
    rc = swap_chain->GetBuffer(i, __uuidof(ID3D12Resource), (void**)&back_tmp);
    if (FAILED(rc))
    {
      ostringstream out;
      out << "Failed to get back buffer " << i << ".  HRESULT = " << rc;
      throw new FrameworkException(out.str());
    }
    device->CreateRenderTargetView(back_tmp, NULL, rtv_handle);
    back_buffer->AddRenderTarget(i, back_tmp, rtv_handle);
    back_tmp->Release();

    rtv_handle.ptr += rtv_desc_size;
  }
  render_target_view->Release();

  back_buffer->UpdateCurrentRenderTarget();

  return back_buffer;
}

D3D12_BackBuffers::D3D12_BackBuffers(UINT num, ID3D12DescriptorHeap* render_target_view, IDXGISwapChain3* swap_chain)
:m_num(num),
 m_render_target_heap(render_target_view),
 m_curr_render_target(0),
 m_swap_chain(swap_chain)
{
  m_render_target_heap->AddRef();
  m_targets = new const D3D12_RenderTarget*[num];
}

D3D12_BackBuffers::~D3D12_BackBuffers()
{
  for (UINT i = 0; i < m_num; i++)
  {
    delete m_targets[i];
  }
  delete[] m_targets;

  m_render_target_heap->Release();
}

void D3D12_BackBuffers::AddRenderTarget(UINT index, ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw new FrameworkException("index beyond number of render targets");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_targets[index] = new D3D12_RenderTarget(target, handle);
}

void D3D12_BackBuffers::UpdateCurrentRenderTarget()
{
  m_curr_render_target = m_swap_chain->GetCurrentBackBufferIndex();
}

const RenderTarget& D3D12_BackBuffers::GetCurrentRenderTarget() const
{
  return *(m_targets[m_curr_render_target]);
}
