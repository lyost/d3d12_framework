#ifndef D3D12_INPUT_LAYOUT_H
#define D3D12_INPUT_LAYOUT_H

#include <d3d12.h>
#include "Graphics/InputLayout.h"
#include "Graphics/Semantics.h"

/// <summary>
/// Describes the input layout for a vertex shader
/// </summary>
class D3D12_InputLayout : public InputLayout
{
  public:
    /// <summary>
    /// An empty layout with the specified number of elements
    /// </summary>
    /// <param name="num">
    /// number of elements that make up the layout
    /// </param>
    D3D12_InputLayout(UINT num);
    
    ~D3D12_InputLayout();
    
    /// <summary>
    /// Sets the input element description of the next entry in the layout
    /// </summary>
    /// <remarks>
    /// Requires:
    /// 1) per vertex data to be tightly packed, starting at offset 0, and
    ///    in the order they are added to the layout instance
    /// 2) per instance data to be tightly packed, starting at offset 0, and
    ///    in the order they are added to the layout instance
    /// </remarks>
    /// <param name="semantic">
    /// which semantic to use for the entry
    /// </remarks>
    /// </param>
    /// <param name="index">
    /// semantic index
    /// </param>
    /// <param name="format">
    /// format of the entry
    /// </param>
    /// <param name="input_slot">
    /// input slot to use
    /// </param>
    /// <param name="instance">
    /// true if this is for per instance data
    /// false for per vertex
    /// </param>
    /// <param name="step_rate">
    /// number of instances to draw before moving to the next instance specific
    /// data
    /// <remarks>
    /// only needs to be specified if instance is true
    /// </remarks>
    /// </param>
    void SetNextElement(Semantics semantic, UINT index, GraphicsDataFormat format, UINT input_slot, bool instance, UINT step_rate = 1);
    
    /// <summary>
    /// Retrieves the number of elements in the layout
    /// </summary>
    /// <returns>
    /// number of elements
    /// </returns>
    UINT GetNum() const;

    /// <summary>
    /// Retrieves the next index of the layout array to set
    /// </summary>
    /// <returns>
    /// next index to set
    /// </returns>
    UINT GetNextIndex() const;
    
    /// <summary>
    /// Retrieves the D3D11 layout description
    /// </summary>
    /// <returns>
    /// D3D11 layout
    /// </returns>
    const D3D12_INPUT_ELEMENT_DESC* GetLayout() const;
    
  private:
    // disabled
    D3D12_InputLayout();
    D3D12_InputLayout(const D3D12_InputLayout& cpy);
    D3D12_InputLayout& operator=(const D3D12_InputLayout& cpy);
    
    /// <summary>
    /// array of input element descriptions that make up the layout
    /// </summary>
    D3D12_INPUT_ELEMENT_DESC* m_layout;
    
    /// <summary>
    /// number of entries in m_layout
    /// </summary>
    UINT m_num;
    
    /// <summary>
    /// index into m_layout of the next element to set
    /// </summary>
    UINT m_next;
};

#endif /* D3D12_INPUT_LAYOUT_H */
