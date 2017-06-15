#ifndef D3D12_VERTEX_BUFFER_ARRAY_H
#define D3D12_VERTEX_BUFFER_ARRAY_H

#include <d3d12.h>
#include "Graphics/Buffers/VertexBufferArray.h"

/// <summary>
/// Container of multiple vertex buffers and allows for quickly sending multiple vertex buffers to the input assembler stage
/// </summary>
class D3D12_VertexBufferArray : public VertexBufferArray
{
  public:
    /// <summary>
    /// Creates a vertex buffer array with the specified number of elements. The array is initialized to all elements clear of a vertex buffer.
    /// </summary>
    /// <param name="num_buffers">
    /// number of buffers that will be in the array
    /// </param>
    D3D12_VertexBufferArray(UINT num_buffers);
    
    ~D3D12_VertexBufferArray();
    
    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from
    /// this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBuffer_Custom& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBuffer_Position& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBuffer_PositionTextureU& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBuffer_PositionTextureUV& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBuffer_PositionTextureUVNormal& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBuffer_PositionTextureUVW& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBuffer_PositionColor& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from
    /// this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBufferGPU_Custom& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBufferGPU_Position& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBufferGPU_PositionTextureU& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBufferGPU_PositionTextureUV& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBufferGPU_PositionTextureUVNormal& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBufferGPU_PositionTextureUVW& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If a vertex buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const VertexBufferGPU_PositionColor& buffer);

    /// <summary>
    /// Sets the element at that specified index to the specified buffer
    /// <summary>
    /// <remarks>
    /// If the buffer is to be destroyed, then it must be cleared from this before the array is used again
    /// </remarks>
    /// <param name="index">
    /// where in the array to set the buffer
    /// </param>
    /// <param name="buffer">
    /// buffer to set the element to
    /// </param>
    void Set(UINT index, const StreamOutputBuffer& buffer);
    
    /// <summary>
    /// Removes any vertex buffer from the specified index
    /// </summary>
    /// <param name="index">
    /// which index to clear
    /// </param>
    void Clear(UINT index);

    /// <summary>
    /// Retrieves the number of buffers the array was created to hold
    /// </summary>
    /// <returns>
    /// number of entries in the array
    /// </returns>
    UINT GetNumBuffers() const;

    /// <summary>
    /// Retrieves the array of D3D12 buffers
    /// </summary>
    /// <returns>
    /// D3D12 array of the buffers
    /// </returns>
    const D3D12_VERTEX_BUFFER_VIEW* GetArray() const;
    
  private:
    // disabled
    D3D12_VertexBufferArray();
    D3D12_VertexBufferArray(const D3D12_VertexBufferArray& cpy);
    D3D12_VertexBufferArray& operator=(const D3D12_VertexBufferArray& cpy);
    
    /// <summary>
    /// D3D12 vertex buffers
    /// </summary>
    D3D12_VERTEX_BUFFER_VIEW* m_vertex_buffers;
    
    /// <summary>
    /// number of elements in m_vertex_buffers
    /// </summary>
    UINT m_num;
};

#endif /* D3D12_VERTEX_BUFFER_ARRAY_H */
