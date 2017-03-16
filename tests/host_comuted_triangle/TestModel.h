#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Graphics/GraphicsCore.h"

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
