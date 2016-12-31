#ifndef D3D12_COMMANDLIST_H
#define D3D12_COMMANDLIST_H

#include <d3d12.h>
#include "Graphics/CommandList.h"

/// <summary>
/// Interface for list of commands for the rendering process
/// </summary>
class D3D12_CommandList : public CommandList
{
  public:
    /// <summary>
    /// Creates a D3D12 direct command list
    ///</summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="pipeline">
    /// Optional pipleline state to use initally for the command list.  This should be NULL if no inital pipeline is to be specified for the command list.
    /// </param>
    /// <returns>
    /// pointer to the command list
    /// </returns>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    static D3D12_CommandList* Create(const GraphicsCore& graphics, Pipeline* pipeline);

    ~D3D12_CommandList();

    /// <summary>
    /// Resets the command list back to its initial state
    /// </summary>
    /// <param name="pipeline">
    /// Optional pipleline state to use initally for the command list.  This should be NULL if no inital pipeline is to be specified for the command list.
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void Reset(Pipeline* pipeline);

    /// <summary>
    /// Informs the command list that recording of commands is complete
    /// </summary>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void Close();

    /// <summary>
    /// Sets the root signature that is applicable to the subsequent member function calls
    /// </summary>
    /// <param name="sig">
    /// Root signature to use
    /// </param>
    void SetRootSignature(const RootSignature& sig);

    /// <summary>
    /// Sets descriptor heaps
    /// </summary>
    /// <param name="heap_array">
    /// heap array to use
    /// </param>
    void SetHeapArray(const HeapArray& heap_array);

    /// <summary>
    /// Sets the root signature slot to the specified constant buffer
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the constant buffer to
    /// </param>
    /// <param name="constant_buffer">
    /// constant buffer to use
    /// </param>
    void SetConstantBuffer(UINT slot, const ConstantBuffer& constant_buffer);

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture1D& texture);

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture2D& texture);

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture2DRenderTarget& texture);

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture3D& texture);

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture1DArray& texture);

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    void SetTextureAsStartOfDescriptorTable(UINT slot, const Texture2DArray& texture);

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    void SetTextureAsStartOfDescriptorTable(UINT slot, const TextureCube& texture);

    /// <summary>
    /// Sets the root signature descriptor table to use the specified texture as the start of the descriptor table
    /// <remarks>
    /// The rest of the root signature descriptor table entries are inferred from the number of table entries and using the subsequent entries in the texture's descriptor heap
    /// </remarks>
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    void SetTextureAsStartOfDescriptorTable(UINT slot, const TextureCubeArray& texture);

    /// <summary>
    /// Sets the topology to use for vertex data passed to the input assembler stage
    /// </summary>
    /// <param name="topology">
    /// topology for vertex data passed to the input assembler stage
    /// </param>
    void IASetTopology(IATopology topology);

    /// <summary>
    /// Sets the vertex buffers to pass to the input assembler stage
    /// </summary>
    /// <param name="buffers">
    /// vertex buffers to pass to the input assembler stage
    /// </param>
    void IASetVertexBuffers(const VertexBufferArray& buffers);

    /// <summary>
    /// Sets the index buffer to pass to the input assembler stage
    /// </summary>
    /// <param name="buffer">
    /// index buffer to pass to the input assembler stage
    /// </param>
    void IASetIndexBuffer(const IndexBuffer& buffer);

    /// <summary>
    /// Sets the viewport to use for the rasterizer stage
    /// </summary>
    /// <param name="viewport">
    /// The viewports to make active
    /// </param>
    void RSSetViewport(const Viewport& viewport);

    /// <summary>
    /// Sets the viewports to use for the rasterizer stage
    /// </summary>
    /// <param name="viewports">
    /// All the viewports to make active
    /// </param>
    void RSSetViewports(const Viewports& viewports);

    /// <summary>
    /// Sets the viewports to use for the rasterizer stage
    /// </summary>
    /// <param name="viewports">
    /// All the viewports to make active
    /// </param>
    /// <param name="start">
    /// index of the first viewport to apply to the rendering pipeline
    /// </param>
    /// <param name="num">
    /// number of viewports to apply
    /// </param>
    void RSSetViewports(const Viewports& viewports, UINT start, UINT num);

    /// <summary>
    /// Sets the scissor rect to use for the rasterizer stage
    /// </summary>
    /// <param name="rect">
    /// the scissor rect to make active
    /// </param>
    void RSSetScissorRect(const RECT& rect);

    /// <summary>
    /// Sets the scissor rects to use for the rasterizer stage
    /// </summary>
    /// <param name="rects">
    /// All the scissor rects to make active
    /// </param>
    void RSSetScissorRects(const std::vector<RECT>& rects);

    /// <summary>
    /// Sets the scissor rects to use for the rasterizer stage
    /// </summary>
    /// <param name="rects">
    /// array of the scissor rects to make active
    /// </param>
    /// <param name="start">
    /// index of the first scissor rect to apply to the rendering pipeline
    /// </param>
    /// <param name="num">
    /// number of scissor to apply
    /// </param>
    void RSSetScissorRects(const std::vector<RECT>& rects, UINT start, UINT num);

    /// <summary>
    /// Preps a render target of a back buffer for use as a render target
    /// </summary>
    /// <param name="target">
    /// Render target to prepare for being drawn to
    /// </param>
    void PrepRenderTarget(const RenderTarget& target);

    /// <summary>
    /// Preps a render target of a back buffer for being presented to the screen
    /// </summary>
    /// <param name="target">
    /// Render target to prepare for being presented
    /// </param>
    void RenderTargetToPresent(const RenderTarget& target);

    /// <summary>
    /// Prepares a texture to be used as a render target by the corresponding RenderTarget instance
    /// </summary>
    /// <param name="texture">
    /// texture to be used as a render target
    /// </param>
    void TextureToRenderTarget(const Texture2DRenderTarget& texture);

    /// <summary>
    /// Allows the render target to be used as a texture by the corresponding Texture2DRenderTarget instance
    /// </summary>
    /// <param name="target">
    /// Render target to allow to be used as a texture
    /// </param>
    void RenderTargetToTexture(const RenderTarget& target);

    /// <summary>
    /// Clears a render target with the specified color
    /// </summary>
    /// <param name="target">
    /// Render target to clear
    /// </param>
    /// <param name="clear_color">
    /// array of a RGBA color with each component in the [0,1] range to use as the clear color for the render target
    /// </param>
    void ClearRenderTarget(const RenderTarget& target, const float clear_color[4]);

    /// <summary>
    /// Clears the depth portion of a depth stencil
    /// </summary>
    /// <param name="depth_stencil">
    /// depth stencil to clear
    /// </param>
    /// <param name="depth_clear_value">
    /// value to use for clearing the depth stencil
    /// </param>
    void ClearDepthStencil(const DepthStencil& depth_stencil, float depth_clear_value);

    /// <summary>
    /// Sets the render target to use for the output merger stage
    /// </summary>
    /// <param name="target">
    /// render target to use
    /// </param>
    void OMSetRenderTarget(const RenderTarget& target);

    /// <summary>
    /// Sets the render target to use for the output merger stage
    /// </summary>
    /// <param name="target">
    /// render target to use
    /// </param>
    /// <param name="depth_stencil">
    /// depth stencil to use
    /// </param>
    void OMSetRenderTarget(const RenderTarget& target, const DepthStencil& depth_stencil);

    // todo: create OMSetRenderTargets to set multiple render targets at once

    /// <summary>
    /// Draws instances of indexed primitives
    /// </summary>
    /// <param name="indices_per_instance">
    /// number of indices for each instance
    /// </param>
    /// <param name="instance_cnt">
    /// number of instances
    /// </param>
    /// <param name="start_index">
    /// index in the instance buffer to start at
    /// </param>
    void DrawIndexedInstanced(UINT indices_per_instance, UINT instance_cnt, UINT start_index);

    /// <summary>
    /// Draws instances of primitives
    /// </summary>
    /// <param name="vertices_per_instance">
    /// number of vertices for each instance
    /// </param>
    /// <param name="instance_cnt">
    /// number of instances
    /// </param>
    /// <param name="start_index">
    /// index in the instance buffer to start at
    /// </param>
    void DrawInstanced(UINT vertices_per_instance, UINT instance_cnt, UINT start_index);

    /// <summary>
    /// Retrieves the D3D12 command list
    /// </summary>
    /// <returns>
    /// D3D12 command list
    /// </returns>
    ID3D12GraphicsCommandList* GetCommandList() const;
    
  private:
    D3D12_CommandList(ID3D12GraphicsCommandList* command_list, ID3D12CommandAllocator* allocated_from);

    // disabled
    D3D12_CommandList();
    D3D12_CommandList(const D3D12_CommandList& cpy);
    D3D12_CommandList& operator=(const D3D12_CommandList& cpy);
    
    /// <summary>
    /// array of input element descriptions that make up the layout
    /// </summary>
    ID3D12GraphicsCommandList* m_command_list;
    
    /// <summary>
    /// number of entries in m_layout
    /// </summary>
    ID3D12CommandAllocator* m_allocated_from;
};

#endif /* D3D12_COMMANDLIST_H */
