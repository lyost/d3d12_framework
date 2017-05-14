#ifndef TEST_MODEL_POS_COLOR_H
#define TEST_MODEL_POS_COLOR_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"

class TestModelPosColor
{
  public:
    /// <summary>
    /// Creates a test model.  The command list must execute followed by a fence after the instance is created.
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="command_list">
    /// command list to write the upload commands to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    TestModelPosColor(GraphicsCore& graphics, CommandList& command_list);

    ~TestModelPosColor();

    /// <summary>
    /// Preps the command list for uploading the initial or modified state to the vertex buffer.  The command list must execute followed by a fence for the transfer to be completed.
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="initial">
    /// true if the vertex buffer should be updated to its initial false
    /// false for a modified state
    /// </param>
    /// <param name="command_list">
    /// command list to write the upload commands to
    /// </param>
    void UpdateVertexBuffer(GraphicsCore& graphics, bool initial, CommandList& command_list);

    /// <summary>
    /// Retrieves the vertex buffer for the model
    /// </summary>
    /// <returns>
    /// vertex buffer
    /// </returns>
    const VertexBufferGPU_PositionColor* GetVertexBuffer() const;

    /// <summary>
    /// Retrieves the index buffer for the model
    /// </summary>
    /// <returns>
    /// index buffer
    /// </returns>
    const IndexBufferGPU16* GetIndexBuffer() const;

  private:
    // disabled
    TestModelPosColor();
    TestModelPosColor(const TestModelPosColor& cpy);
    TestModelPosColor& operator=(const TestModelPosColor& cpy);

    /// <summary>
    /// vertex buffer for the test case
    /// </summary>
    VertexBuffer_PositionColor* m_verts;

    /// <summary>
    /// GPU-only vertex buffer for the test case
    /// </summary>
    VertexBufferGPU_PositionColor* m_gpu_verts;

    /// <summary>
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;

    /// <summary>
    /// GPU-only index buffer for the test case
    /// </summary>
    IndexBufferGPU16* m_gpu_indices;

    /// <summary>
    /// vertex buffer data
    /// </summary>
    Vertex_PositionColor m_vert_data[4];
};

#endif /* TEST_MODEL_POS_COLOR_H */
