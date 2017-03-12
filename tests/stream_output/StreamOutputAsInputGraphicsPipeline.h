#ifndef STREAM_OUTPUT_AS_INPUT_GRAPHICS_PIPELINE_H
#define STREAM_OUTPUT_AS_INPUT_GRAPHICS_PIPELINE_H

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
#include "TestModel.h"
#include "Camera.h"
#include "TestGraphicsPipeline.h"

class StreamOutputAsInputGraphicsPipeline
{
  public:
    StreamOutputAsInputGraphicsPipeline(GraphicsCore& graphics, TestGraphicsPipeline& normal_pipeline);
    ~StreamOutputAsInputGraphicsPipeline();

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
    /// <param name="normal_pipeline">
    /// the test case graphics pipeline that goes through the normal rendering process and writes to the stream output buffer
    /// </param>
    void Resize(GraphicsCore& graphics, TestGraphicsPipeline& normal_pipeline);

  private:
    // disabled
    StreamOutputAsInputGraphicsPipeline();
    StreamOutputAsInputGraphicsPipeline(const StreamOutputAsInputGraphicsPipeline& cpy);
    StreamOutputAsInputGraphicsPipeline& operator=(const StreamOutputAsInputGraphicsPipeline& cpy);

    /// <summary>
    /// cameras for the test viewport
    /// </summary>
    const Camera* m_camera;

    /// <summary>
    /// root signatures for when the stream output buffer is used as input to the input assembler stage
    /// </summary>
    RootSignature* m_so_root_sig;

    /// <summary>
    /// vertex buffer array for using m_so_buffer as a vertex buffer for drawing
    /// </summary>
    VertexBufferArray* m_so_vert_array;

    /// <summary>
    /// vertex shader for when the stream output buffer is used as input to the input assembler stage
    /// </summary>
    Shader* m_so_vertex_shader;

    /// <summary>
    /// graphics pipeline for when the stream output buffer is used as input to the input assembler stage
    /// </summary>
    Pipeline* m_so_pipeline;

    /// <summary>
    /// readback buffer for determining how many vertices were written to the stream output buffer
    /// </summary>
    ReadbackBuffer* m_readback;

    /// <summary>
    /// command list to draw with
    /// </summary>
    CommandList* m_command_list;

    /// <summary>
    /// stream output buffer (stored as a vector due to StreamOutputBuffer::GetNumVerticesWrittenD3D12 expecting a vector for performance reasons)
    /// </summary>
    std::vector<StreamOutputBuffer*> m_so_buffers;

    /// <summary>
    /// corresponding scissor rect for m_viewports's first viewport
    /// </summary>
    RECT m_scissor_rect;

    /// <summary>
    /// depth stencil
    /// </summary>
    DepthStencil* m_depth_stencil;

    /// <summary>
    /// Constant buffer 
    /// </summary>
    ConstantBuffer* m_constant_buffer;

    /// <summary>
    /// array of descriptor heaps
    /// </summary>
    HeapArray* m_heap_array;
};

#endif /* STREAM_OUTPUT_AS_INPUT_GRAPHICS_PIPELINE_H */
