#ifndef D3D12_VERTEX_BUFFER_H
#define D3D12_VERTEX_BUFFER_H

#include <d3d12.h>
#include "public_inc/Graphics/GraphicsCore.h"

namespace D3D12_VertexBuffer
{
  /// <summary>
  /// Creates a vertex buffer
  /// </summary>
  /// <param name="graphics">
  /// core graphics interface
  /// </param>
  /// <param name="stride">
  /// size of each entry in bytes
  /// </param>
  /// <param name="num">
  /// number of entries in the buffer
  /// </param>
  /// <param name="data">
  /// initial data for the vertex buffer
  /// </param>
  /// <param name="buffer">
  /// output parameter for where to put the created vertex buffer
  /// </param>
  /// <param name="view">
  /// output parameter for where to put the created vertex buffer view
  /// </param>
  /// <exception cref="FrameworkException">
  /// Thrown when an error is encountered
  /// </exception>
  void CreateBuffer(GraphicsCore& graphics, UINT stride, UINT num, const void* data, ID3D12Resource*& buffer, D3D12_VERTEX_BUFFER_VIEW& view);
}

#endif /* D3D12_VERTEX_BUFFER_H */
