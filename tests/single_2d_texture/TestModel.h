#ifndef TEST_MODEL_H
#define TEST_MODEL_H

#include <vector>
#include "Graphics/GraphicsCore.h"
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
    const VertexBuffer_PositionTextureUV* GetVertexBuffer() const;

    /// <summary>
    /// Retrieves the first texture in the descriptor heap for the model
    /// </summary>
    /// <returns>
    /// model's first texture in the descriptor heap
    /// </returns>
    const Texture2D* GetTexture() const;

  private:
    // disabled
    TestModel();
    TestModel(const TestModel& cpy);
    TestModel& operator=(const TestModel& cpy);

    /// <summary>
    /// Helper function for creating the texture image
    /// </summary>
    /// <param name="bytes">
    /// where to write the bytes of the texture image to
    /// </param>
    void CreateTextureImage(std::vector<UINT8>& bytes) const;

    /// <summary>
    /// vertex buffer for the test case
    /// </summary>
    VertexBuffer_PositionTextureUV* m_verts;

    /// <summary>
    /// texture
    /// </summary>
    Texture2D* m_texture;
};

#endif /* TEST_MODEL_H */
