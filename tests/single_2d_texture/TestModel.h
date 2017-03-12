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

    const VertexBuffer_PositionTexture* GetVertexBuffer() const;

    const Texture2D* GetTexture() const;

    UINT GetNumVertices() const;

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
    VertexBuffer_PositionTexture* m_verts;

    /// <summary>
    /// texture
    /// </summary>
    Texture2D* m_texture;

    /// <summary>
    /// buffer for uploading the texture's data
    /// </summary>
    TextureUploadBuffer* m_upload_texture;
};

#endif /* TEST_MODEL_H */
