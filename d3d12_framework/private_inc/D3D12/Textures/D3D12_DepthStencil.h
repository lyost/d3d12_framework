#ifndef D3D12_DEPTH_STENCIL_H
#define D3D12_DEPTH_STENCIL_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/DepthStencil.h"

class D3D12_DepthStencil : public DepthStencil
{
  public:
    /// <summary>
    /// Creates D3D12 depth stencils for each entry in configs placed into out in the same order as entries in the configs array
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="configs">
    /// Configurations for depth stencils to create
    /// </param>
    /// <param name="out">
    /// Where to put the created depth stencils.  They will be added to the end of the array.
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static void Create(const GraphicsCore& graphics, const std::vector<Config>& configs, std::vector<DepthStencil*>& out);

    ~D3D12_DepthStencil();

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

    D3D12_DepthStencil(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, D3D12_CPU_DESCRIPTOR_HANDLE cpu_mem, UINT width, UINT height, UINT64 upload_size, ID3D12DescriptorHeap* desc_heap);

    /// <summary>
    /// Determines the size depth stencil will need to be to hold the requested number of bytes
    /// </summary>
    /// <param name="device">
    /// d3d12 device
    /// </param>
    /// <param name="config">
    /// configuration to use for the depth stencil
    /// </param>
    /// <returns>
    /// number of bytes the depth stencil should be created with
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static UINT GetAlignedSize(ID3D12Device* device, const Config& config);


    /// <summary>
    /// Helper function to fill in a D3D12 resource description struct
    /// </summary>
    /// <param name="config">
    /// configuration to use for the depth stencil
    /// </param>
    /// <param name="resource_desc">
    /// output paramenter of the resource description struct to fill in
    /// </param>
    static void GetResourceDesc(const Config& config, D3D12_RESOURCE_DESC& resource_desc);

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

    /// <summary>
    /// width of the depth stencil in pixels
    /// </summary>
    UINT m_width;

    /// <summary>
    /// height of the depth stencil in pixels
    /// </summary>
    UINT m_height;

    /// <summary>
    /// D3D12 descriptor heap that the depth stencil was created from
    /// </summary>
    ID3D12DescriptorHeap* m_desc_heap;
};

#endif /* D3D12_DEPTH_STENCIL_H */
