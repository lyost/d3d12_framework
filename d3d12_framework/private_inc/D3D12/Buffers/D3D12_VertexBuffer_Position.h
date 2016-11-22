#ifndef D3D12_VERTEXBUFFER_POSITION_H
#define D3D12_VERTEXBUFFER_POSITION_H

#include <d3d12.h>
#include "Graphics/Buffers/VertexBuffer_Position.h"

class D3D12_VertexBufferArray;

/// <summary>
/// Vertex buffer whose only element is position
/// </summary>
class D3D12_VertexBuffer_Position : public VertexBuffer_Position
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
    /// <param name="data">
    /// initial data for the vertex buffer
    /// </param>
    static D3D12_VertexBuffer_Position* Create(GraphicsCore& graphics, UINT num, const Vertex_Position* data);
    
    /// <summary>
    /// Cleans up the vertex buffer
    /// </summary>
    ~D3D12_VertexBuffer_Position();

    /// <summary>
    /// Retrieves the number of entries in the buffer
    /// </summary>
    /// <returns>
    /// number of entries
    /// </returns>
    UINT GetNumVertices() const;
    
  private:
    // disabled
    D3D12_VertexBuffer_Position();
    D3D12_VertexBuffer_Position(const D3D12_VertexBuffer_Position& cpy);
    D3D12_VertexBuffer_Position& operator=(const D3D12_VertexBuffer_Position& cpy);
    
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
    D3D12_VertexBuffer_Position(UINT num, ID3D12Resource* buffer, const D3D12_VERTEX_BUFFER_VIEW& view);

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

#endif /* D3D12_VERTEXBUFFER_POSITION_H */
