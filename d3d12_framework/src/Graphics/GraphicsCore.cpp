#include "Graphics/GraphicsCore.h"
#include "private_inc/D3D12/D3D12_Core.h"

GraphicsCore* GraphicsCore::CreateD3D12(HWND& wnd)
{
  return D3D12_Core::Create(wnd);
}

GraphicsCore::GraphicsCore()
{
}

GraphicsCore::~GraphicsCore()
{
}
