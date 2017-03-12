#ifndef TEST_GRAPHICS_PIPELINE_H
#define TEST_GRAPHICS_PIPELINE_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Shader.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Pipeline.h"
#include "Graphics/CommandListBundle.h"
#include "Graphics/HeapArray.h"
#include "TestModel.h"

class TestGraphicsPipeline
{
  public:
    TestGraphicsPipeline(GraphicsCore& graphics);
    ~TestGraphicsPipeline();

    /// <summary>
    /// Retrieves the shader resource descriptor heap for the pipeline
    /// </summary>
    /// <returns>
    /// shader resource descriptor heap
    /// </returns>
    ShaderResourceDescHeap* GetShaderResourceDescHeap() const;

    /// <summary>
    /// Retrieves the command list for the pipeline
    /// </summary>
    /// <returns>
    /// the pipeline's command list
    /// </returns>
    CommandList* GetCommandList() const;

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

    /// <summary>
    /// Informs the pipeline the core graphics interface has processed a resize event
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void Resize(GraphicsCore& graphics);

  private:
    // disabled
    TestGraphicsPipeline();
    TestGraphicsPipeline(const TestGraphicsPipeline& cpy);
    TestGraphicsPipeline& operator=(const TestGraphicsPipeline& cpy);

    /// <summary>
    /// test model
    /// </summary>
    const TestModel* m_model;

    /// <summary>
    /// root signatures for the test case
    /// </summary>
    RootSignature* m_root_sig;

    /// <summary>
    /// test vertex shader
    /// </summary>
    Shader* m_vertex_shader;

    /// <summary>
    /// test pixel shader
    /// </summary>
    Shader* m_pixel_shader;

    /// <summary>
    /// input layouts for the vertex shader
    /// </summary>
    InputLayout* m_input_layout;

    /// <summary>
    /// graphics pipeline
    /// </summary>
    Pipeline* m_pipeline;

    /// <summary>
    /// command list to draw with
    /// </summary>
    CommandList* m_command_list;

    /// <summary>
    /// Descriptor Heap for allocating the buffers from
    /// </summary>
    ShaderResourceDescHeap* m_shader_buffer_heap;

    /// <summary>
    /// array of descriptor heaps
    /// </summary>
    HeapArray* m_heap_array;

    /// <summary>
    /// viewports to use
    /// </summary>
    Viewports m_viewports;

    /// <summary>
    /// corresponding scissor rect for m_viewports's first viewport
    /// </summary>
    RECT m_scissor_rect;

    /// <summary>
    /// vertex buffer array for supplying the vertex buffer to the rendering process
    /// </summary>
    VertexBufferArray* m_vert_array;
};

#endif /* TEST_GRAPHICS_PIPELINE_H */
