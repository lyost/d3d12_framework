#ifndef D3D12_VERTEX_BUFFER_H
#define D3D12_VERTEX_BUFFER_H

#include <d3d12.h>
#include "public_inc/Graphics/GraphicsCore.h"

namespace D3D12_VertexBuffer
{
  /// <summary>
  /// Creates a vertex buffer that is writable by the CPU
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

  /// <summary>
  /// Creates a vertex buffer that is only accessible to the GPU
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
  /// <param name="buffer">
  /// output parameter for where to put the created vertex buffer
  /// </param>
  /// <param name="view">
  /// output parameter for where to put the created vertex buffer view
  /// </param>
  /// <exception cref="FrameworkException">
  /// Thrown when an error is encountered
  /// </exception>
  void CreateBufferGPU(GraphicsCore& graphics, UINT stride, UINT num, ID3D12Resource*& buffer, D3D12_VERTEX_BUFFER_VIEW& view);

  /// <summary>
  /// Preps the command list for uploading the contents of the vertex buffer to the specified GPU-only accessible vertex buffer.  The command list must execute followed by a fence for the transfer to be
  /// completed.
  /// </summary>
  /// <param name="graphics">
  /// core graphics interface
  /// </param>
  /// <param name="command_list">
  /// command list to use for uploading
  /// </param>
  /// <param name="src">
  /// vertex buffer to upload from
  /// </param>
  /// <param name="dst">
  /// GPU-only vertex buffer to upload to
  /// </param>
  /// <exception cref="FrameworkException">
  /// Thrown when an error is encountered
  /// </exception>
  void PrepUpload(GraphicsCore& graphics, CommandList& command_list, ID3D12Resource* src, ID3D12Resource* dst);
}

#endif /* D3D12_VERTEX_BUFFER_H */
