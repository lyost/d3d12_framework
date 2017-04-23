#ifndef TEST_GRAPHICS_PIPELINE_POS_TEX_UVW_H
#define TEST_GRAPHICS_PIPELINE_POS_TEX_UVW_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Shader.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Pipeline.h"
#include "Graphics/CommandListBundle.h"
#include "Graphics/ShaderResourceDescHeap.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/HeapArray.h"
#include "TestModelPosTexUVW.h"
#include "Camera.h"

class TestGraphicsPipelinePosTexUVW
{
  public:
    TestGraphicsPipelinePosTexUVW(GraphicsCore& graphics);
    ~TestGraphicsPipelinePosTexUVW();

    /// <summary>
    /// Retrieves the shader resource descriptor heap for the pipeline
    /// </summary>
    /// <returns>
    /// shader resource descriptor heap
    /// </returns>
    ShaderResourceDescHeap* GetShaderResourceDescHeap() const;

    /// <summary>
    /// Sets the model to render.  Since this test program only uses 1 model, this is a set function instead of adding to a collection.
    /// </summary>
    /// <param name="model">
    /// model to render
    /// </param>
    void SetModel(const TestModelPosTexUVW* model);

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
    /// <param name="command_list">
    /// command list to issue draw commands to
    /// </param>
    void Draw(GraphicsCore& graphics, CommandList& command_list);

  private:
    // disabled
    TestGraphicsPipelinePosTexUVW();
    TestGraphicsPipelinePosTexUVW(const TestGraphicsPipelinePosTexUVW& cpy);
    TestGraphicsPipelinePosTexUVW& operator=(const TestGraphicsPipelinePosTexUVW& cpy);

    /// <summary>
    /// test model
    /// </summary>
    const TestModelPosTexUVW* m_model;

    /// <summary>
    /// cameras for the test viewport
    /// </summary>
    const Camera* m_camera;

    /// <summary>
    /// root signatures for the test case
    /// </summary>
    RootSignature* m_root_sig;

    /// <summary>
    /// graphics pipeline
    /// </summary>
    Pipeline* m_pipeline;

    /// <summary>
    /// vertex buffer array for supplying the vertex buffer to the rendering process
    /// </summary>
    VertexBufferArray* m_vert_array;

    /// <summary>
    /// viewports to use
    /// </summary>
    Viewports m_viewports;

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
};

#endif /* TEST_GRAPHICS_PIPELINE_POS_TEX_UVW_H */
