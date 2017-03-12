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

    const VertexBuffer_Position* GetVertexBuffer() const;

    const IndexBuffer16* GetIndexBuffer() const;

    const TextureCubeArray* GetTexture() const;

    UINT GetNumVertices() const;

  private:
    // disabled
    TestModel();
    TestModel(const TestModel& cpy);
    TestModel& operator=(const TestModel& cpy);

    /// <summary>
    /// Creates a test texture
    /// </summary>
    /// <param name="cube">
    /// index of which cube the texture is for
    /// </param>
    /// <param name="side">
    /// index of which side of the cube the texture is for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture(UINT16 cube, UINT16 side, std::vector<UINT8>& bytes);

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
    TextureCubeArray* m_texture;

    /// <summary>
    /// buffer for uploading the texture's data
    /// </summary>
    std::vector<TextureUploadBuffer*> m_upload_texture;
};

#endif /* TEST_MODEL_H */
