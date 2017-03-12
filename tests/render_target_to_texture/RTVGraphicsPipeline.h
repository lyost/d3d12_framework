#ifndef RTV_GRAPHICS_PIPELINE_H
#define RTV_GRAPHICS_PIPELINE_H

class TestGraphicsPipeline;

#include "Graphics/GraphicsCore.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Shader.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Pipeline.h"
#include "Graphics/CommandListBundle.h"
#include "Graphics/ShaderResourceDescHeap.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/HeapArray.h"
#include "TestTextureEnums.h"
#include "TestGraphicsPipeline.h"
#include "TestModel.h"
#include "Camera.h"

class RTVGraphicsPipeline
{
  public:
    RTVGraphicsPipeline(GraphicsCore& graphics, const TestGraphicsPipeline& main_pipeline);
    ~RTVGraphicsPipeline();

    /// <summary>
    /// Sets the model to render.  Since this test program only uses 1 model, this is a set function instead of adding to a collection.
    /// </summary>
    /// <param name="model">
    /// model to render
    /// </param>
    void SetModel(const TestModel* model);

    /// <summary>
    /// Draws the current frame
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void Draw(GraphicsCore& graphics);

  private:
    // disabled
    RTVGraphicsPipeline();
    RTVGraphicsPipeline(const RTVGraphicsPipeline& cpy);
    RTVGraphicsPipeline& operator=(const RTVGraphicsPipeline& cpy);

    /// <summary>
    /// test model
    /// </summary>
    const TestModel* m_model;

    /// <summary>
    /// root signatures for the test case
    /// </summary>
    RootSignature* m_root_sig;

    /// <summary>
    /// graphics pipeline for creating the test texture
    /// </summary>
    Pipeline* m_rtv_pipeline;

    /// <summary>
    /// command list to draw with
    /// </summary>
    CommandList* m_command_list;

    /// <summary>
    /// array of descriptor heaps
    /// </summary>
    HeapArray* m_heap_array;

    /// <summary>
    /// Constant buffer 
    /// </summary>
    ConstantBuffer* m_constant_buffer;

    /// <summary>
    /// pixel shader for creating the test texture
    /// </summary>
    Shader* m_rtv_pixel_shader;

    /// <summary>
    /// render target view of m_texture
    /// </summary>
    RenderTarget* m_rtv_texture;

    /// <summary>
    /// depth stencil
    /// </summary>
    DepthStencil* m_depth_stencil;

    /// <summary>
    /// vertex buffer array for supplying the vertex buffer to the rendering process
    /// </summary>
    VertexBufferArray* m_vert_array;
};

#endif /* RTV_GRAPHICS_PIPELINE_H */
