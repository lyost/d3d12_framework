#ifndef D3D12_RENDER_TARGET_H
#define D3D12_RENDER_TARGET_H

#include <d3d12.h>
#include "Graphics/Buffers/RenderTarget.h"

/// <summary>
/// Wrapper for a D3D12 render target
/// </summary>
class D3D12_RenderTarget : public RenderTarget
{
  public:
    D3D12_RenderTarget(ID3D12Resource* target, D3D12_CPU_DESCRIPTOR_HANDLE handle);
    ~D3D12_RenderTarget();

    /// <summary>
    /// Retrieves the D3D12 resource of the render target
    /// </summary>
    /// <returns>
    /// D3D12 resource for the texture
    /// </returns>
    ID3D12Resource* GetResource() const;

    /// <summary>
    /// Retrieves the D3D12 CPU descriptor handle for the render target
    /// </summary>
    /// <returns>
    /// D3D12 CPU descriptor handle
    /// </returns>
    const D3D12_CPU_DESCRIPTOR_HANDLE& GetHandle() const;
    
  private:
    // disabled
    D3D12_RenderTarget();
    D3D12_RenderTarget(const D3D12_RenderTarget& cpy);
    D3D12_RenderTarget& operator=(const D3D12_RenderTarget& cpy);

    /// <summary>
    /// render target
    /// </summary>
    ID3D12Resource* m_render_target;

    /// <summary>
    /// CPU descriptor handle for render target
    /// </summary>
    D3D12_CPU_DESCRIPTOR_HANDLE m_rtv_handle;
};

#endif /* D3D12_RENDER_TARGET_H */