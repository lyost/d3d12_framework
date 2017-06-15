#ifndef D3D12_VERTEXBUFFER_GPU_POSITION_TEXTURE_UV_NORMAL_H
#define D3D12_VERTEXBUFFER_GPU_POSITION_TEXTURE_UV_NORMAL_H

#include <d3d12.h>
#include "Graphics/Buffers/VertexBufferGPU_PositionTextureUVNormal.h"

class D3D12_VertexBufferArray;

/// <summary>
/// Vertex buffer whose elements are position, texture uv coordinates, and a 3d normal vector
/// </summary>
class D3D12_VertexBufferGPU_PositionTextureUVNormal : public VertexBufferGPU_PositionTextureUVNormal
{
  public:
    /// <summary>
    /// Creates a vertex buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <returns>
    /// pointer to the vertex buffer instance
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static D3D12_VertexBufferGPU_PositionTextureUVNormal* Create(GraphicsCore& graphics, UINT num);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    ~D3D12_VertexBufferGPU_PositionTextureUVNormal();

    /// <summary>
    /// Retrieves the number of entries in the buffer
    /// </summary>
    /// <returns>
    /// number of entries
    /// </returns>
    UINT GetNumVertices() const;

    /// <summary>
    /// Retrieves the D3D12 resource
    /// </summary>
    /// <returns>
    /// D3D12 resource for the vertex buffer
    /// </returns>
    ID3D12Resource* GetResource() const;
    
  private:
    // disabled
    D3D12_VertexBufferGPU_PositionTextureUVNormal();
    D3D12_VertexBufferGPU_PositionTextureUVNormal(const D3D12_VertexBufferGPU_PositionTextureUVNormal& cpy);
    D3D12_VertexBufferGPU_PositionTextureUVNormal& operator=(const D3D12_VertexBufferGPU_PositionTextureUVNormal& cpy);
    
    /// <summary>
    /// Creates a vertex buffer
    /// </summary>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <param name="buffer">
    /// vertex buffer
    /// </param>
    /// <param name="view">
    /// vertex buffer view
    /// </param>
    /// <param name="type">
    /// which type of texture coordinates are stored in this vertex buffer
    /// </param>
    D3D12_VertexBufferGPU_PositionTextureUVNormal(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view);

    /// <summary>
    /// number of entries in the buffer
    /// </summary>
    UINT m_num;

    /// <summary>
    /// vertex buffer
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// vertex buffer view, used to provide data to the command list for rendering
    /// </summary>
    D3D12_VERTEX_BUFFER_VIEW m_view;

    // allow D3D12_VertexBufferArray full access to the members since it is an optimization for multiple vertex buffers
    friend D3D12_VertexBufferArray;
};

#endif /* D3D12_VERTEXBUFFER_GPU_POSITION_TEXTURE_UV_NORMAL_H */
