#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"

class TestModel
{
  public:
    TestModel(GraphicsCore& graphics);
    ~TestModel();

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
    TestModel();
    TestModel(const TestModel& cpy);
    TestModel& operator=(const TestModel& cpy);

    /// <summary>
    /// vertex buffer for the test case
    /// </summary>
    VertexBuffer_PositionColor* m_verts;

    /// <summary>
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;
};

#endif /* TEST_MODEL_H */
