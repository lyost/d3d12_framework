#ifndef D3D12_TEXTURE2D_ARRAY_H
#define D3D12_TEXTURE2D_ARRAY_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Textures/Texture2DArray.h"

class D3D12_Texture2DArray : public Texture2DArray
{
  public:
    /// <summary>
    /// Determines the size the texture array will need to be to hold the requested number of bytes
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="height">
    /// height of the texture in pixels
    /// </param>
    /// <param name="length">
    /// number of textures in the array
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// number of bytes the texture should be created with
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static UINT GetAlignedSize(const GraphicsCore& graphics, UINT width, UINT height, UINT16 length, GraphicsDataFormat format);

    /// <summary>
    /// Creates a D3D12 texture array
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="resource_heap">
    /// texture upload resource heap to put the texture into
    /// </param>
    /// <param name="shader_buffer_heap">
    /// shader resources descriptor heap that the texture will be accessed from
    /// </param>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="height">
    /// height of the texture in pixels
    /// </param>
    /// <param name="length">
    /// number of textures in the array
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <returns>
    /// D3D12 texture 2D array
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static Texture2DArray* Create(const GraphicsCore& graphics, TextureResourceHeap& resource_heap, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 length,
      GraphicsDataFormat format);

    ~D3D12_Texture2DArray();

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

  private:
    // disabled
    D3D12_Texture2DArray();
    D3D12_Texture2DArray(const D3D12_Texture2DArray& cpy);
    D3D12_Texture2DArray& operator=(const D3D12_Texture2DArray& cpy);

    D3D12_Texture2DArray(ID3D12Resource* buffer, D3D12_GPU_DESCRIPTOR_HANDLE gpu_mem, UINT width, UINT height, UINT16 length, GraphicsDataFormat format, UINT64 upload_size);

    /// <summary>
    /// Helper function to fill in a D3D12 resource description struct
    /// </summary>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="height">
    /// height of the texture in pixels
    /// </param>
    /// <param name="format">
    /// texture format
    /// </param>
    /// <param name="length">
    /// number of textures in the array
    /// </param>
    /// <param name="resource_desc">
    /// output paramenter of the resource description struct to fill in
    /// </param>
    static void GetResourceDesc(UINT width, UINT height, UINT16 length, GraphicsDataFormat format, D3D12_RESOURCE_DESC& resource_desc);

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
    /// <summary>
    UINT m_width;

    /// <summary>
    /// height of the texture in pixels
    /// <summary>
    UINT m_height;

    /// <summary>
    /// length of the texture array
    /// <summary>
    UINT16 m_length;

    /// <summary>
    /// texture format
    /// <summary>
    GraphicsDataFormat m_format;
};

#endif /* D3D12_TEXTURE2D_ARRAY_H */
