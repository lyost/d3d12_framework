#ifndef D3D12_INDEX_BUFFER16_H
#define D3D12_INDEX_BUFFER16_H

#include <d3d12.h>
#include "Graphics/Buffers/IndexBuffer16.h"

/// <summary>
/// Index buffer for 16bit long entries
/// </summary>
class D3D12_IndexBuffer16 : public IndexBuffer16
{
  public:
    /// <summary>
    /// Creates an index buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <param name="data">
    /// initial data for the index buffer
    /// </param>
    static D3D12_IndexBuffer16* Create(GraphicsCore& graphics,UINT num, const WORD* data);
    
    ~D3D12_IndexBuffer16();

    /// <summary>
    /// Retrieves the number of indices in the buffer
    /// </summary>
    /// <returns>
    /// number of indices
    /// </returns>
    UINT GetNumIndices() const;

    /// <summary>
    /// Retrieves the D3D12 index buffer
    /// </summary>
    /// <returns>
    /// D3D12 index buffer
    /// </returns>
    const D3D12_INDEX_BUFFER_VIEW& GetBuffer() const;
    
  private:
    // disabled
    D3D12_IndexBuffer16();
    D3D12_IndexBuffer16(const D3D12_IndexBuffer16& cpy);
    D3D12_IndexBuffer16& operator=(const D3D12_IndexBuffer16& cpy);

    /// <summary>
    /// Creates an index buffer
    /// </summary>
    /// <param name="num">
    /// number of indices in the buffer
    /// </param>
    /// <param name="buffer">
    /// index buffer
    /// </param>
    /// <param name="view">
    /// index buffer view
    /// </param>
    D3D12_IndexBuffer16(UINT num, ID3D12Resource* buffer, D3D12_INDEX_BUFFER_VIEW& view);

    /// <summary>
    /// number of indices in the buffer
    /// </summary>
    UINT m_num;

    /// <summary>
    /// index buffer
    /// </summary>
    ID3D12Resource* m_buffer;

    /// <summary>
    /// index buffer view, used to provide data to the command list for rendering
    /// </summary>
    D3D12_INDEX_BUFFER_VIEW m_view;
};

#endif /* D3D12_INDEX_BUFFER16_H */
