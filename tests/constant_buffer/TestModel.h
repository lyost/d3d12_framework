#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/VertexBuffer_PositionColor.h"

class TestModel
{
  public:
    TestModel(GraphicsCore& graphics);
    ~TestModel();

    const VertexBuffer_PositionColor* GetVertexBuffer() const;

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
};

#endif /* TEST_MODEL_H */
