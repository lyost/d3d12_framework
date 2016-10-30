#ifndef INPUT_LAYOUT_H
#define INPUT_LAYOUT_H

#include <windows.h>
#include "Graphics/Semantics.h"
#include "Graphics/GraphicsDataFormat.h"

/// <summary>
/// Describes the input layout for a vertex shader
/// </summary>
class InputLayout
{
  public:
    /// <summary>
    /// Creates a blank D3D12 input layout with the specified number of entries to be configured via SetNextElement
    /// </summary>
    /// <param name="num">
    /// number of elements that make up the layout
    /// </param>
    /// <returns>
    /// pointer to the input layout instance on success
    /// NULL on error
    /// </returns>
    static InputLayout* CreateD3D12(UINT num);

    virtual ~InputLayout();
    
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
    /// </param>
    /// <param name="index">
    /// semantic index
    /// </param>
    /// <param name="format">
    /// format of the entry
    /// <remarks>
    /// Looked into alternatives to taking a DXGI_FORMAT here, but the enum has
    /// so many different types that can be used as input to a vertex shader
    /// that it is impractical to do anything besides take it directly for now
    /// </remarks>
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
    /// <returns>
    /// true if the element was successfully set
    /// false otherwise (e.g. no element was available to be set)
    /// </returns>
    virtual bool SetNextElement(Semantics semantic, UINT index, GraphicsDataFormat format, UINT input_slot, bool instance, UINT step_rate = 1) = 0;

  protected:
    InputLayout();
    
  private:
    // disabled
    InputLayout(const InputLayout& cpy);
    InputLayout& operator=(const InputLayout& cpy);
};

#endif /* INPUT_LAYOUT_H */
