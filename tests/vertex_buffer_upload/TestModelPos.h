#ifndef TEST_MODEL_POS_H
#define TEST_MODEL_POS_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"

class TestModelPos
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
    TestModelPos(GraphicsCore& graphics, CommandList& command_list);

    ~TestModelPos();

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
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    void UpdateVertexBuffer(GraphicsCore& graphics, bool initial, CommandList& command_list);

    /// <summary>
    /// Retrieves the vertex buffer for the model
    /// </summary>
    /// <returns>
    /// vertex buffer
    /// </returns>
    const VertexBufferGPU_Position* GetVertexBuffer() const;

    /// <summary>
    /// Retrieves the index buffer for the model
    /// </summary>
    /// <returns>
    /// index buffer
    /// </returns>
    const IndexBuffer16* GetIndexBuffer() const;

  private:
    // disabled
    TestModelPos();
    TestModelPos(const TestModelPos& cpy);
    TestModelPos& operator=(const TestModelPos& cpy);

    /// <summary>
    /// vertex buffer for the test case
    /// </summary>
    VertexBuffer_Position* m_verts;

    /// <summary>
    /// GPU-only vertex buffer for the test case
    /// </summary>
    VertexBufferGPU_Position* m_gpu_verts;

    /// <summary>
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;

    /// <summary>
    /// vertex buffer data
    /// </summary>
    Vertex_Position m_vert_data[4];
};

#endif /* TEST_MODEL_POS_H */
