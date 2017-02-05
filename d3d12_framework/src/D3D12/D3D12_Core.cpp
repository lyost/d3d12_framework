#include <sstream>
#include <dxgidebug.h>
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_CommandListBundle.h"
#include "private_inc/D3D12/D3D12_CommandList.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
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
    throw FrameworkException("Failed to get debug controller");
  }
#endif

  IDXGIFactory4* factory;
  rc = CreateDXGIFactory1(__uuidof(IDXGIFactory4), (void**)&factory);
  if (FAILED(rc))
  {
    throw FrameworkException("Failed to create DXGI factory");
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
    throw FrameworkException("Failed to create device");
  }

  D3D12_COMMAND_QUEUE_DESC queue_desc = {};
  queue_desc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
  queue_desc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
  rc = device->CreateCommandQueue(&queue_desc, __uuidof(ID3D12CommandQueue), (void**)&command_queue);
  if (FAILED(rc))
  {
    throw FrameworkException("Failed to create command queue");
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
    throw FrameworkException("Failed to create the swap chain");
  }
  rc = swap_chain->QueryInterface(__uuidof(IDXGISwapChain3), (void**)&swap_chain3);
  if (FAILED(rc))
  {
    throw FrameworkException("Failed to convert swap chain");
  }

  factory->Release();

  back_buffer = D3D12_BackBuffers::Create(device, swap_chain3);

  rc = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, __uuidof(ID3D12Fence), (void**)&fence);
  if (FAILED(rc))
  {
    throw FrameworkException("Failed to create fence");
  }

  fence_event = CreateEventEx(NULL, NULL, FALSE, EVENT_ALL_ACCESS);
  if (fence_event == NULL)
  {
    ostringstream out;
    out << "Failed to create fence event. Error code: " << GetLastError();
    throw FrameworkException(out.str());
  }

  D3D12_VIEWPORT vp;
  vp.Width    = (FLOAT)width;
  vp.Height   = (FLOAT)height;
  vp.MinDepth = 0.0f;
  vp.MaxDepth = 1.0f;
  vp.TopLeftX = 0;
  vp.TopLeftY = 0;

  return new D3D12_Core(device, fence, fence_event, swap_chain, swap_chain3, command_queue, back_buffer, vp);
}

D3D12_Core::D3D12_Core(ID3D12Device* device, ID3D12Fence* fence, HANDLE fence_event, IDXGISwapChain* swap_chain_base, IDXGISwapChain3* swap_chain, ID3D12CommandQueue* command_queue,
  D3D12_BackBuffers* back_buffer, const D3D12_VIEWPORT& viewport)
:m_device(device),
 m_fence(fence),
 m_fence_event(fence_event),
 m_swap_chain_base(swap_chain_base),
 m_swap_chain(swap_chain),
 m_command_queue(command_queue),
 m_back_buffer(back_buffer),
 m_fullscreen(false)
{
  memcpy(&m_default_viewport, &viewport, sizeof(Viewport));
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
  delete m_back_buffer;
  m_swap_chain->Release();
  m_swap_chain_base->Release();
  m_command_queue->Release();
  m_device->Release();
}

void D3D12_Core::Fullscreen(UINT width,UINT height,bool enable)
{
  HRESULT rc;
  
  // get the current swap chain description and update to the desired width and height
  DXGI_SWAP_CHAIN_DESC desc_swap;
  rc = m_swap_chain->GetDesc(&desc_swap);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to get swap chain description.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }
  desc_swap.BufferDesc.Width  = width;
  desc_swap.BufferDesc.Height = height;
  
  // find the closest matching mode
  IDXGIOutput* monitor = NULL;
  rc = m_swap_chain->GetContainingOutput(&monitor);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to get swap chain output.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }
  DXGI_MODE_DESC match;
  rc = monitor->FindClosestMatchingMode(&desc_swap.BufferDesc,&match,m_device);
  monitor->Release();
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to find closest matching mode.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }
  
  // inform the swap chain of the change in resolution
  rc = m_swap_chain->ResizeTarget(&match);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to resize target.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }
  
  // go full screen
  rc = m_swap_chain->SetFullscreenState(enable,NULL);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to set the full screen state.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }
  
  // take care of refresh rate issues
  match.RefreshRate.Numerator   = 0;
  match.RefreshRate.Denominator = 0;
  rc = m_swap_chain->ResizeTarget(&match);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to take care of refresh rate issue.  HRESULT: " << rc;
    throw FrameworkException(out.str());
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
    ostringstream out;
    out << "Error resizing swap chain.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }

  m_back_buffer = D3D12_BackBuffers::Create(m_device, m_swap_chain);

  m_default_viewport.width  = (float)width;
  m_default_viewport.height = (float)height;
}

void D3D12_Core::WaitOnFence()
{
  // todo: Make thread-safe or a separate thread-safe version of the function
  const UINT64 fence_val = m_fence_value;
  HRESULT rc = m_command_queue->Signal(m_fence, fence_val);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed signaling command queue for fence.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }
  ++m_fence_value;

  if (m_fence->GetCompletedValue() < fence_val)
  {
    rc = m_fence->SetEventOnCompletion(fence_val, m_fence_event);
    if (FAILED(rc))
    {
      ostringstream out;
      out << "Failed waiting on fence event.  HRESULT: " << rc;
      throw FrameworkException(out.str());
    }
    WaitForSingleObject(m_fence_event, INFINITE);
  }
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

UINT D3D12_Core::CheckSupportedMultisampleLevels(GraphicsDataFormat format, UINT sample_count, bool tiled) const
{
  D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS query;
  query.Format           = (DXGI_FORMAT)format;
  query.SampleCount      = sample_count;
  query.Flags            = tiled ? D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_TILED_RESOURCE : D3D12_MULTISAMPLE_QUALITY_LEVELS_FLAG_NONE;
  query.NumQualityLevels = 0;

  HRESULT rc = m_device->CheckFeatureSupport(D3D12_FEATURE_MULTISAMPLE_QUALITY_LEVELS, &query, sizeof(query));
  if (FAILED(rc))
  {
    throw FrameworkException("Failed to get multisample quality information");
  }

  return query.NumQualityLevels;
}

ID3D12Device* D3D12_Core::GetDevice() const
{
  return m_device;
}
