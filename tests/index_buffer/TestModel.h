#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"

class TestModel
{
  public:
    TestModel(GraphicsCore& graphics);
    ~TestModel();

    const VertexBuffer_PositionColor* GetVertexBuffer() const;

    const IndexBuffer16* GetIndexBuffer() const;

    UINT GetNumVertices() const;

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
