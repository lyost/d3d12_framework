#ifndef TEST_GRAPHICS_PIPELINE_H
#define TEST_GRAPHICS_PIPELINE_H

class StreamOutputAsInputGraphicsPipeline;

#include "Graphics/GraphicsCore.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Shader.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Pipeline.h"
#include "Graphics/CommandListBundle.h"
#include "Graphics/ShaderResourceDescHeap.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/HeapArray.h"
#include "TestModel.h"
#include "Camera.h"
#include "StreamOutputAsInputGraphicsPipeline.h"

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
    /// Sets a camera for the viewport
    /// </summary>
    /// <param name="cam">
    /// camera to use for the viewport
    /// </param>
    void SetCamera(const Camera* cam);

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
    /// Helper function for creating the depth stencil on load and on resize
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void CreateDepthStencil(GraphicsCore& graphics);

    /// <summary>
    /// test model
    /// </summary>
    const TestModel* m_model;

    /// <summary>
    /// cameras for the test viewport
    /// </summary>
    const Camera* m_camera;

    /// <summary>
    /// root signatures for the test case
    /// </summary>
    RootSignature* m_root_sig;

    /// <summary>
    /// test vertex shader
    /// </summary>
    Shader* m_vertex_shader;

    /// <summary>
    /// test hull shader
    /// </summary>
    Shader* m_hull_shader;

    /// <summary>
    /// test domain shader
    /// </summary>
    Shader* m_domain_shader;

    /// <summary>
    /// test geometry shader
    /// </summary>
    Shader* m_geometry_shader;

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
    /// vertex buffer array for supplying the vertex buffer to the rendering process
    /// </summary>
    VertexBufferArray* m_vert_array;

    /// <summary>
    /// viewports to use
    /// </summary>
    Viewports m_viewports;

    /// <summary>
    /// corresponding scissor rect for m_viewports's first viewport
    /// </summary>
    RECT m_scissor_rect;

    /// <summary>
    /// Descriptor Heap for allocating the buffers from
    /// </summary>
    ShaderResourceDescHeap* m_shader_buffer_heap;

    /// <summary>
    /// array of descriptor heaps
    /// </summary>
    HeapArray* m_heap_array;

    /// <summary>
    /// Constant buffer 
    /// </summary>
    ConstantBuffer* m_constant_buffer;

    /// <summary>
    /// Constant buffer for resetting the stream output buffer
    /// </summary>
    ConstantBuffer* m_scratch_buffer;

    /// <summary>
    /// depth stencil
    /// </summary>
    DepthStencil* m_depth_stencil;

    /// <summary>
    /// stream output buffer (stored as a vector due to StreamOutputBuffer::GetNumVerticesWrittenD3D12 expecting a vector for performance reasons)
    /// </summary>
    std::vector<StreamOutputBuffer*> m_so_buffers;

    /// <summary>
    /// array of stream output buffers
    /// </summary>
    StreamOutputBufferArray* m_so_array;

    friend StreamOutputAsInputGraphicsPipeline;
};

#endif /* TEST_GRAPHICS_PIPELINE_H */
