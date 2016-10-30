#ifndef D3D12_DEPTH_STENCIL_H
#define D3D12_DEPTH_STENCIL_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/DepthStencil.h"

class D3D12_DepthStencil : public DepthStencil
{
  public:
    /// <summary>
    /// Determines the size depth stencil will need to be to hold the requested number of bytes
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="width">
    /// width in pixels
    /// </param>
    /// <param name="height">
    /// height in pixels
    /// </param>
    /// <returns>
    /// number of bytes the depth stencil should be created with
    /// -1 if the computed size is too large
    /// </returns>
    static UINT GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height);

    /// <summary>
    /// Creates a D3D12 depth stencil
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="resource_heap">
    /// depth stencil resource heap to put the depth stencil into
    /// <remarks>
    /// It is the caller's responsibility to make sure there is enough room in the heap for the new buffer
    /// </remarks>
    /// </param>
    /// <param name="depth_stencil_buffer_heap">
    /// depth stencil resources descriptor heap that the depth stencil will be accessed from
    /// <remarks>
    /// It is the caller's responsibility to make sure there is enough room in the heap for the new buffer
    /// </remarks>
    /// </param>
    /// <param name="width">
    /// width of the depth stencil in pixels
    /// </param>
    /// <param name="height">
    /// height of the depth stencil in pixels
    /// </param>
    /// <param name="default_depth_clear">
    /// default value to use for clearing the depth stencil
    /// </param>
    /// <returns>
    /// D3D12 depth stencil on success
    /// NULL on error
    /// </returns>
    static D3D12_DepthStencil* Create(const GraphicsCore& graphics, DepthStencilResourceHeap& resource_heap, DepthStencilDescHeap& depth_stencil_buffer_heap, UINT width, UINT height,
      float default_depth_clear);

    ~D3D12_DepthStencil();

    /// <summary>
    /// Retrieves the required size for a depth stencil upload buffer that matches this depth stencil
    /// </summary>
    /// <returns>
    /// required number of bytes in the upload buffer
    /// </returns>
    UINT64 GetUploadBufferSize() const;

    /// <summary>
    /// Retrieves the D3D12 resource
    /// </summary>
    /// <returns>
    /// D3D12 resource for the depth stencil
    /// </returns>
    ID3D12Resource* GetBuffer() const;

    /// <summary>
    /// Retrieves the GPU address for the depth stencil
    /// </summary>
    /// <returns>
    /// GPU address for the depth stencil
    /// </returns>
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUAddr() const;

    /// <summary>
    /// Retrieves the D3D12 CPU descriptor handle for the depth stencil
    /// </summary>
    /// <returns>
    /// D3D12 CPU descriptor handle
    /// </returns>
    const D3D12_CPU_DESCRIPTOR_HANDLE& GetHandle() const;

  private:
    // disabled
    D3D12_DepthStencil();
    D3D12_DepthStencil(const D3D12_DepthStencil& cpy);
    D3D12_DepthStencil& operator=(const D3D12_DepthStencil& cpy);

    D3D12_DepthStencil(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, D3D12_CPU_DESCRIPTOR_HANDLE cpu_mem, UINT width, UINT height, UINT64 upload_size);

    /// <summary>
    /// Helper function to fill in a D3D12 resource description struct
    /// </summary>
    /// <param name="width">
    /// width of the depth stencil in pixels
    /// </param>
    /// <param name="height">
    /// height of the depth stencil in pixels
    /// </param>
    /// <param name="resource_desc">
    /// output paramenter of the resource description struct to fill in
    /// </param>
    static void GetResourceDesc(UINT width, UINT height, D3D12_RESOURCE_DESC& resource_desc);

    /// <summary>
    /// D3D12 depth stencil resource
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// GPU address for the depth stencil
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE m_gpu_mem;

    /// <summary>
    /// CPU descriptor handle for depth stencil
    /// </summary>
    D3D12_CPU_DESCRIPTOR_HANDLE m_cpu_handle;

    /// <param name="width">
    /// width of the depth stencil in pixels
    /// </param>
    UINT m_width;

    /// <param name="height">
    /// height of the depth stencil in pixels
    /// </param>
    UINT m_height;

    /// <param name="format">
    /// number of bytes needed in an upload buffer for this depth stencil
    /// </param>
    UINT64 m_upload_size;
};

#endif /* D3D12_DEPTH_STENCIL_H */
