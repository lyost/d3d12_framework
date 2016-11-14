#include <sstream>
#include <dxgidebug.h>
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_CommandListBundle.h"
#include "private_inc/D3D12/D3D12_CommandList.h"
#include "log.h"
using namespace std;

// todo: move this to exist entirely in D3D12_BackBuffer and query it
const UINT NumRenderTargets = 2;

D3D12_Core* D3D12_Core::Create(HWND& wnd)
{
  HRESULT rc = S_OK;
  
  // vars needed for setting up D3D12
  ID3D12Device*           device             = NULL;
  IDXGISwapChain*         swap_chain         = NULL;
  IDXGISwapChain3*        swap_chain3        = NULL;
  ID3D12CommandQueue*     command_queue      = NULL;
  ID3D12CommandAllocator* command_alloc      = NULL;
  ID3D12Fence*            fence              = NULL;
  HANDLE                  fence_event;

  // this library's wrappers around vars needed for setting up D3D12
  D3D12_BackBuffers*      back_buffer;

  // determine the window width and height
  RECT rect;
  GetClientRect(wnd, &rect);
  UINT width  = rect.right  - rect.left;
  UINT height = rect.bottom - rect.top;

#if _DEBUG
  ID3D12Debug* debug_controller;
  if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debug_controller))))
  {
    debug_controller->EnableDebugLayer();
  }
  else
  {
    log_print("Failed to get debug controller\n");
  }
#endif

  IDXGIFactory4* factory;
  rc = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&factory);
  if (FAILED(rc))
  {
    log_print("Failed to create DXGI factory\n");
    return false;
  }

  UINT i = 0;
  IDXGIAdapter1* adapter = NULL;
  while (factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND)
  {
    rc = D3D12CreateDevice(adapter, D3D_FEATURE_LEVEL_12_0, __uuidof(ID3D12Device), (void**)&device);
    if (FAILED(rc))
    {
      device = NULL;
    }
    else
    {
      break;
    }

    ++i;
  }
  if (device == NULL)
  {
    log_print("Failed to create device\n");
    return NULL;
  }

  D3D12_COMMAND_QUEUE_DESC queue_desc = {};
  queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
  rc = device->CreateCommandQueue(&queue_desc, __uuidof(ID3D12CommandQueue), (void**)&command_queue);
  if (FAILED(rc))
  {
    log_print("Failed to create command queue\n");
    return NULL;
  }

  DXGI_SWAP_CHAIN_DESC sd = {};
  sd.BufferCount       = NumRenderTargets;
  sd.BufferDesc.Width  = width;
  sd.BufferDesc.Height = height;
  sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
  sd.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
  sd.SwapEffect        = DXGI_SWAP_EFFECT_FLIP_DISCARD;
  sd.OutputWindow      = wnd;
  sd.SampleDesc.Count  = 1;
  sd.Windowed          = true;
  rc = factory->CreateSwapChain(command_queue, &sd, &swap_chain);
  if (FAILED(rc))
  {
    log_print("Failed to create the swap chain\n");
    return NULL;
  }
  rc = swap_chain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&swap_chain3);
  if (FAILED(rc))
  {
    log_print("Failed to convert swap chain\n");
    return NULL;
  }

  factory->Release();

  back_buffer = D3D12_BackBuffers::Create(device, swap_chain3);

  rc = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&command_alloc);
  if (FAILED(rc))
  {
    log_print("Failed to create command allocator\n");
    return NULL;
  }

  rc = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**)&fence);
  if (FAILED(rc))
  {
    log_print("Failed to create fence\n");
    return NULL;
  }

  fence_event = CreateEventEx(NULL, NULL, FALSE, EVENT_ALL_ACCESS);
  if (fence_event == NULL)
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to create fence event. Error code: " << GetLastError() << '\n';
      log_print(out.str().c_str());
    }
    return NULL;
  }

  // todo: Setup the viewport
  D3D12_VIEWPORT vp;
  vp.Width    = (FLOAT)width;
  vp.Height   = (FLOAT)height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;

  return new D3D12_Core(device, fence, fence_event, swap_chain, swap_chain3, command_alloc, command_queue, back_buffer, vp);
}

D3D12_Core::D3D12_Core(ID3D12Device* device, ID3D12Fence* fence, HANDLE fence_event, IDXGISwapChain* swap_chain_base, IDXGISwapChain3* swap_chain, ID3D12CommandAllocator* command_alloc,
  ID3D12CommandQueue* command_queue, D3D12_BackBuffers* back_buffer, const D3D12_VIEWPORT& viewport)
:m_device(device),
 m_fence(fence),
 m_fence_event(fence_event),
 m_swap_chain_base(swap_chain_base),
 m_swap_chain(swap_chain),
 m_command_alloc(command_alloc),
 m_command_queue(command_queue),
 m_back_buffer(back_buffer),
 m_fullscreen(false)
{
  memcpy(&m_default_viewport, &viewport, sizeof(Viewport));

  /*
  // create the default blend and depth stencil states
  m_blend_state = BlendState::GetCurrent(m_immediate_context);
  m_depth_state = DepthStencilState::GetCurrent(m_immediate_context);
  
  // create the wrapped versions of the depth stencil view and render target
  // views
  m_depth_view_wrapper = new DepthStencilView(depth_stencil_view);
  m_render_target_view_wrapper = new RenderTargetView(render_target_view);
  */
}

D3D12_Core::~D3D12_Core()
{
  WaitOnFence();

  if (m_fullscreen)
  {
    DXGI_SWAP_CHAIN_DESC desc = {};
    m_swap_chain->GetDesc(&desc);
    Fullscreen(desc.BufferDesc.Width, desc.BufferDesc.Height, false);
  }

  CloseHandle(m_fence_event);
  m_fence->Release();
  m_command_alloc->Release();
  delete m_back_buffer;
  m_swap_chain->Release();
  m_swap_chain_base->Release();
  m_command_queue->Release();
  m_device->Release();
}

void D3D12_Core::Fullscreen(UINT width,UINT height,bool enable)
{
  HRESULT rc;
  
  // get the current swap chain description and update to the desired width and
  // height
  DXGI_SWAP_CHAIN_DESC desc_swap;
  rc = m_swap_chain->GetDesc(&desc_swap);
  if (FAILED(rc))
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to get swap chain description.  Error code: " << rc
          << '\n';
      log_print(out.str().c_str());
    }
    return;
  }
  desc_swap.BufferDesc.Width = width;
  desc_swap.BufferDesc.Height = height;
  
  // find the closest matching mode
  IDXGIOutput* monitor = NULL;
  rc = m_swap_chain->GetContainingOutput(&monitor);
  if (FAILED(rc))
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to get swap chain output.  Error code: " << rc
          << '\n';
      log_print(out.str().c_str());
    }
    return;
  }
  DXGI_MODE_DESC match;
  rc = monitor->FindClosestMatchingMode(&desc_swap.BufferDesc,&match,m_device);
  monitor->Release();
  if (FAILED(rc))
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to find closest matching mode.  Error code: " << rc
          << '\n';
      log_print(out.str().c_str());
    }
    return;
  }
  
  // inform the swap chain of the change in resolution
  rc = m_swap_chain->ResizeTarget(&match);
  if (FAILED(rc))
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to resize target.  Error code: " << rc
          << '\n';
      log_print(out.str().c_str());
    }
    return;
  }
  
  // go full screen
  rc = m_swap_chain->SetFullscreenState(enable,NULL);
  if (FAILED(rc))
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to set the full screen state.  Error code: " << rc
          << '\n';
      log_print(out.str().c_str());
    }
    return;
  }
  
  // take care of refresh rate issues
  match.RefreshRate.Numerator   = 0;
  match.RefreshRate.Denominator = 0;
  rc = m_swap_chain->ResizeTarget(&match);
  if (FAILED(rc))
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Failed to take care of refresh rate issue.  Error code: " << rc
          << '\n';
      log_print(out.str().c_str());
    }
    return;
  }

  m_fullscreen = enable;
}

void D3D12_Core::OnResize(UINT width,UINT height)
{
  WaitOnFence();

  delete m_back_buffer;

  DXGI_SWAP_CHAIN_DESC desc = {};
  m_swap_chain->GetDesc(&desc);
  HRESULT rc = m_swap_chain->ResizeBuffers(desc.BufferCount, width, height, desc.BufferDesc.Format, desc.Flags);
  if (FAILED(rc))
  {
    if (log_would_output())
    {
      ostringstream out;
      out << "Error resizing swap chain: " << rc << '\n';
      log_print(out.str().c_str());
    }
    exit(1);
  }

  m_back_buffer = D3D12_BackBuffers::Create(m_device, m_swap_chain);

  m_default_viewport.width  = (float)width;
  m_default_viewport.height = (float)height;
}

bool D3D12_Core::WaitOnFence()
{
  // todo: Make thread-safe or a separate thread-safe version of the function
  const UINT64 fence_val = m_fence_value;
  if (FAILED(m_command_queue->Signal(m_fence, fence_val)))
  {
    log_print("Failed signaling command queue for fence");
    return false;
  }
  ++m_fence_value;

  if (m_fence->GetCompletedValue() < fence_val)
  {
    if (FAILED(m_fence->SetEventOnCompletion(fence_val, m_fence_event)))
    {
      log_print("Failed waiting on fence event");
      return false;
    }
    WaitForSingleObject(m_fence_event, INFINITE);
  }

  return true;
}

void D3D12_Core::ExecuteCommandList(const CommandList& list) const
{
  ID3D12GraphicsCommandList* command_lists = ((const D3D12_CommandList&)list).GetCommandList();
  m_command_queue->ExecuteCommandLists(1, (ID3D12CommandList*const*)&command_lists);
}

void D3D12_Core::ExecuteCommandLists(const CommandListBundle& lists) const
{
  ID3D12GraphicsCommandList*const* command_lists = ((const D3D12_CommandListBundle&)lists).GetCommandLists();
  m_command_queue->ExecuteCommandLists(lists.GetNumCommandLists(), (ID3D12CommandList*const*)command_lists);
}

void D3D12_Core::Swap()
{
  m_swap_chain->Present(1, 0);
  WaitOnFence();
  m_back_buffer->UpdateCurrentRenderTarget();
}

const Viewport& D3D12_Core::GetDefaultViewport() const
{
  return m_default_viewport;
}

BackBuffers& D3D12_Core::GetBackBuffer() const
{
  return *m_back_buffer;
}

// todo
#if 0

ID3D12DeviceContext* D3D12_Core::GetImmediateContext()
{
  return m_immediate_context;
}

const BlendState& D3D12_Core::GetDefaultBlendState() const
{
  return *m_blend_state;
}

const DepthStencilState& D3D12_Core::GetDefaultDepthStencilState() const
{
  return *m_depth_state;
}

DepthStencilView& D3D12_Core::GetDefaultDepthStencilView() const
{
  return *m_depth_view_wrapper;
}

RenderTargetView& D3D12_Core::GetDefaultRenderTargetView() const
{
  return *m_render_target_view_wrapper;
}

void D3D12_Core::DrawIndexedPrimitives(ID3D12DeviceContext* context,
  D3D12_PRIMITIVE_TOPOLOGY primitive,UINT start_index,UINT num_indices)
{
  // set the primitive topology
  context->IASetPrimitiveTopology(primitive);
  
  // draw
  context->DrawIndexed(num_indices,start_index,0);
}

void D3D12_Core::DrawInstancedPrimitives(ID3D12DeviceContext* context,
  D3D12_PRIMITIVE_TOPOLOGY primitive,UINT start_index,UINT num_indices,
  UINT start_instance,UINT num_instances)
{
  // set the primitive topology
  context->IASetPrimitiveTopology(primitive);
  
  // draw
  context->DrawIndexedInstanced(num_indices,num_instances,start_index,0,
    start_instance);
}

void D3D12_Core::DrawStreamOutput(ID3D12DeviceContext* context,
  D3D12_PRIMITIVE_TOPOLOGY primitive)
{
  // set the primitive topology
  context->IASetPrimitiveTopology(primitive);
  
  // draw
  context->DrawAuto();
}
#endif /* 0 */

ID3D12Device* D3D12_Core::GetDevice() const
{
  return m_device;
}

ID3D12CommandAllocator* D3D12_Core::GetDefaultCommandAlloc() const
{
  return m_command_alloc;
}
