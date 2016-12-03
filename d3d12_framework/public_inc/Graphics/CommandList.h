#ifndef COMMANDLIST_H
#define COMMANDLIST_H

class GraphicsCore;
class RootSignature;
class Pipeline;
class VertexBufferArray;
class HeapArray;
class ConstantBuffer;
class Texture;
class DepthStencil;

#include <vector>
#include "Graphics/GraphicsCore.h"
#include "Graphics/Pipeline.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Viewports.h"
#include "Graphics/Textures/RenderTarget.h"
#include "Graphics/HeapArray.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/Topology.h"
#include "Graphics/Buffers/VertexBufferArray.h"
#include "Graphics/Buffers/IndexBuffer.h"
#include "Graphics/Textures/Texture.h"
#include "Graphics/Textures/DepthStencil.h"

/// <summary>
/// Interface for list of commands for the rendering process
/// </summary>
class CommandList
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
    static CommandList* CreateD3D12Direct(const GraphicsCore& graphics, Pipeline* pipeline);

    virtual ~CommandList();

    /// <summary>
    /// Resets the command list back to its initial state
    /// </summary>
    /// <param name="pipeline">
    /// Optional pipleline state to use initally for the command list.  This should be NULL if no inital pipeline is to be specified for the command list.
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void Reset(Pipeline* pipeline) = 0;

    /// <summary>
    /// Informs the command list that recording of commands is complete
    /// </summary>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void Close() = 0;

    /// <summary>
    /// Sets the root signature that is applicable to the subsequent member function calls
    /// </summary>
    /// <param name="sig">
    /// Root signature to use
    /// </param>
    virtual void SetRootSignature(const RootSignature& sig) = 0;

    /// <summary>
    /// Sets descriptor heaps
    /// </summary>
    /// <param name="heap_array">
    /// heap array to use
    /// </param>
    virtual void SetHeapArray(const HeapArray& heap_array) = 0;

    /// <summary>
    /// Binds the constant buffer to a slot
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the constant buffer to
    /// </param>
    /// <param name="constant_buffer">
    /// constant buffer to use
    /// </param>
    virtual void SetConstantBuffer(UINT slot, const ConstantBuffer& constant_buffer) = 0;

    /// <summary>
    /// Binds the texture to a slot
    /// </summary>
    /// <param name="slot">
    /// index of the slot to bind the texture to
    /// </param>
    /// <param name="texture">
    /// texture to use
    /// </param>
    virtual void SetTexture(UINT slot, const Texture& texture) = 0;

    // todo: overloads for clearing just the stencil, and both depth and stencil

    /*
     * Input assembler functions
     */

      /// <summary>
      /// Sets the topology to use for vertex data passed to the input assembler stage
      /// </summary>
      /// <param name="topology">
      /// topology for vertex data passed to the input assembler stage
      /// </param>
      virtual void IASetTopology(IATopology topology) = 0;

      /// <summary>
      /// Sets the vertex buffers to pass to the input assembler stage
      /// </summary>
      /// <param name="buffers">
      /// vertex buffers to pass to the input assembler stage
      /// </param>
      virtual void IASetVertexBuffers(const VertexBufferArray& buffers) = 0;
      // todo: override to allow for a subset of the buffers to be used

      /// <summary>
      /// Sets the index buffer to pass to the input assembler stage
      /// </summary>
      /// <param name="buffer">
      /// index buffer to pass to the input assembler stage
      /// </param>
      virtual void IASetIndexBuffer(const IndexBuffer& buffer) = 0;

    /*
     * Rasterizer functions
     */

      /// <summary>
      /// Sets the viewport to use for the rasterizer stage
      /// </summary>
      /// <param name="viewport">
      /// The viewports to make active
      /// </param>
      virtual void RSSetViewport(const Viewport& viewport) = 0;

      /// <summary>
      /// Sets the viewports to use for the rasterizer stage
      /// </summary>
      /// <param name="viewports">
      /// All the viewports to make active
      /// </param>
      virtual void RSSetViewports(const Viewports& viewports) = 0;

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
      virtual void RSSetViewports(const Viewports& viewports, UINT start, UINT num) = 0;

      /// <summary>
      /// Sets the scissor rect to use for the rasterizer stage
      /// </summary>
      /// <param name="rect">
      /// the scissor rect to make active
      /// </param>
      virtual void RSSetScissorRect(const RECT& rect) = 0;

      /// <summary>
      /// Sets the scissor rects to use for the rasterizer stage
      /// </summary>
      /// <param name="rects">
      /// array of the scissor rects to make active
      /// </param>
      virtual void RSSetScissorRects(const std::vector<RECT>& rects) = 0;

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
      virtual void RSSetScissorRects(const std::vector<RECT>& rects, UINT start, UINT num) = 0;

    /*
     * Output merger functions
     */

      /// <summary>
      /// Preps a render target of a back buffer for use as a render target
      /// </summary>
      /// <param name="target">
      /// Render target to prepare for being drawn to
      /// </param>
      virtual void PrepRenderTarget(const RenderTarget& target) = 0;

      /// <summary>
      /// Preps a render target of a back buffer for being presented to the screen
      /// </summary>
      /// <param name="target">
      /// Render target to prepare for being presented
      /// </param>
      virtual void RenderTargetToPresent(const RenderTarget& target) = 0;

      /// <summary>
      /// Clears a render target with the specified color
      /// </summary>
      /// <param name="target">
      /// Render target to clear
      /// </param>
      /// <param name="clear_color">
      /// array of a RGBA color with each component in the [0,1] range to use as the clear color for the render target
      /// </param>
      virtual void ClearRenderTarget(const RenderTarget& target, const float clear_color[4]) = 0;

      /// <summary>
      /// Clears the depth portion of a depth stencil
      /// </summary>
      /// <param name="depth_stencil">
      /// depth stencil to clear
      /// </param>
      /// <param name="depth_clear_value">
      /// value to use for clearing the depth stencil
      /// </param>
      virtual void ClearDepthStencil(const DepthStencil& depth_stencil, float depth_clear_value) = 0;

      /// <summary>
      /// Sets the render target to use for the output merger stage
      /// </summary>
      /// <param name="target">
      /// render target to use
      /// </param>
      virtual void OMSetRenderTarget(const RenderTarget& target) = 0;

      /// <summary>
      /// Sets the render target to use for the output merger stage
      /// </summary>
      /// <param name="target">
      /// render target to use
      /// </param>
      /// <param name="depth_stencil">
      /// depth stencil to use
      /// </param>
      virtual void OMSetRenderTarget(const RenderTarget& target, const DepthStencil& depth_stencil) = 0;

      // todo: create OMSetRenderTargets to set multiple render targets at once

    /*
     * Drawing functions
     */

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
      virtual void DrawIndexedInstanced(UINT indices_per_instance, UINT instance_cnt, UINT start_index) = 0;

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
      virtual void DrawInstanced(UINT vertices_per_instance, UINT instance_cnt, UINT start_index) = 0;

  protected:
    CommandList();
    
  private:
    // disabled
    CommandList(const CommandList& cpy);
    CommandList& operator=(const CommandList& cpy);
};

#endif /* COMMANDLIST_H */
