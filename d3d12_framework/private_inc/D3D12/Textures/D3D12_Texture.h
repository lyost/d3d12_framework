#ifndef D3D12_TEXTURE_H
#define D3D12_TEXTURE_H

#include <d3d12.h>
#include "Graphics/GraphicsCore.h"
#include "Graphics/ShaderResourceDescHeap.h"

namespace D3D12_Texture
{
  /// <summary>
  /// Wrapper for the various fields needed for using a created texture
  /// </summary>
  struct CreatedTexture
  {
    /// <summary>
    /// D3D12 resource for the texture
    /// </summary>
    ID3D12Resource* buffer;

    /// <summary>
    /// handle to where the texture is on the GPU
    /// </summary>
    D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle;
  };

  /// <summary>
  /// Creates a D3D12 texture
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
  /// <param name="height">
  /// height of the texture in pixels
  /// </param>
  /// <param name="depth">
  /// depth or array size of the texure
  /// </param>
  /// <param name="format">
  /// texture format
  /// </param>
  /// <param name="dimension">
  /// which dimensions the texture should have
  /// </param>
  /// <returns>
  /// D3D12 texture data
  /// </returns>
  /// <exception cref="FrameworkException">
  /// Thrown when an error is encountered
  /// </exception>
  CreatedTexture Create(const GraphicsCore& graphics, ShaderResourceDescHeap& shader_buffer_heap, UINT width, UINT height, UINT16 depth, GraphicsDataFormat format, D3D12_SRV_DIMENSION dimension,
    D3D12_RESOURCE_FLAGS flags);
}

#endif /* D3D12_TEXTURE_H */
