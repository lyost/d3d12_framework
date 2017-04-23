#ifndef TEST_MODEL_POS_COLOR_H
#define TEST_MODEL_POS_COLOR_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"

class TestModelPosColor
{
  public:
    TestModelPosColor(GraphicsCore& graphics);
    ~TestModelPosColor();

    /// <summary>
    /// Updates the vertex buffer to either its initial state or a modified state
    /// </summary>
    /// <param name="initial">
    /// true if the vertex buffer should be updated to its initial false
    /// false for a modified state
    /// </param?
    void UpdateVertexBuffer(bool initial);

    /// <summary>
    /// Retrieves the vertex buffer for the model
    /// </summary>
    /// <returns>
    /// vertex buffer
    /// </returns>
    const VertexBuffer_PositionColor* GetVertexBuffer() const;

    /// <summary>
    /// Retrieves the index buffer for the model
    /// </summary>
    /// <returns>
    /// index buffer
    /// </returns>
    const IndexBuffer16* GetIndexBuffer() const;

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
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;

    /// <summary>
    /// vertex buffer data
    /// </summary>
    Vertex_PositionColor m_vert_data[4];
};

#endif /* TEST_MODEL_POS_COLOR_H */
