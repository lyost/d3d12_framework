#ifndef D3D12_TEXTURE1D_ARRAY_H
#define D3D12_TEXTURE1D_ARRAY_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/Texture1DArray.h"

class D3D12_Texture1DArray : public Texture1DArray
{
  public:
    /// <summary>
    /// Creates a D3D12 texture array
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="shader_buffer_heap">
    /// shader resources descriptor heap that the texture will be accessed from
    /// </param>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="length">
    /// number of textures in the array
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <param name="mip_levels">
    /// number of mipmap levels
    /// </param>
    /// <returns>
    /// D3D12 texture 1D array
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture1DArray* Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT16 length, GraphicsDataFormat format, UINT16 mip_levels);

    ~D3D12_Texture1DArray();

    /// <summary>
    /// Retrieves the number of textures in the array
    /// </summary>
    /// <returns>
    /// number of textures in the array
    /// </returns>
    UINT16 GetLength() const;

    /// <summary>
    /// Retrieves the D3D12 resource
    /// </summary>
    /// <returns>
    /// D3D12 resource for the texture
    /// </returns>
    ID3D12Resource* GetBuffer() const;

    /// <summary>
    /// Retrieves the GPU address for the texture
    /// </summary>
    /// <returns>
    /// GPU address for the texture
    /// </returns>
    D3D12_GPU_DESCRIPTOR_HANDLE GetGPUAddr() const;

    /// <summary>
    /// Retrieves the number of mipmap levels the resource was created with
    /// </summary>
    /// <returns>
    /// GPU address for the texture
    /// </returns>
    UINT16 GetNumMipmapLevels() const;

  private:
    // disabled
    D3D12_Texture1DArray();
    D3D12_Texture1DArray(const D3D12_Texture1DArray& cpy);
    D3D12_Texture1DArray& operator=(const D3D12_Texture1DArray& cpy);

    D3D12_Texture1DArray(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT16 length, GraphicsDataFormat format, UINT16 num_mip_levels);

    /// <summary>
    /// D3D12 texture resource
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// GPU address for the texture
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE m_gpu_mem;

    /// <summary>
    /// width of the texture in pixels
    /// </summary>
    UINT m_width;

    /// <summary>
    /// length of the texture array
    /// <summary>
    UINT16 m_length;

    /// <summary>
    /// texture format
    /// </summary>
    GraphicsDataFormat m_format;

    /// <summary>
    /// number of mipmap levels in the resource
    /// </summary>
    UINT16 m_num_mipmap_levels;
};

#endif /* D3D12_TEXTURE1D_ARRAY_H */
