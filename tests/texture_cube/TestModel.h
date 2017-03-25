#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"

class TestModel
{
  public:
    TestModel(GraphicsCore& graphics, ShaderResourceDescHeap* shader_buffer_heap, CommandList* command_list);
    ~TestModel();

    /// <summary>
    /// Retrieves the vertex buffer for the model
    /// </summary>
    /// <returns>
    /// vertex buffer
    /// </returns>
    const VertexBuffer_Position* GetVertexBuffer() const;

    /// <summary>
    /// Retrieves the index buffer for the model
    /// </summary>
    /// <returns>
    /// index buffer
    /// </returns>
    const IndexBuffer16* GetIndexBuffer() const;

    /// <summary>
    /// Retrieves the first texture in the descriptor heap for the model
    /// </summary>
    /// <returns>
    /// model's first texture in the descriptor heap
    /// </returns>
    const TextureCube* GetTexture() const;

  private:
    // disabled
    TestModel();
    TestModel(const TestModel& cpy);
    TestModel& operator=(const TestModel& cpy);

    /// <summary>
    /// Creates a test texture
    /// </summary>
    /// <param name="side">
    /// index of which side of the cube the texture is for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture(UINT16 side, std::vector<UINT8>& bytes);

    /// <summary>
    /// vertex buffer for the test case
    /// </summary>
    VertexBuffer_Position* m_verts;

    /// <summary>
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;

    /// <summary>
    /// texture
    /// </summary>
    TextureCube* m_texture;
};

#endif /* TEST_MODEL_H */
