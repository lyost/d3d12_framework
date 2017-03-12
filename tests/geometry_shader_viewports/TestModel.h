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

    const VertexBuffer_PositionTexture* GetVertexBuffer() const;

    const IndexBuffer16* GetIndexBuffer() const;

    const Texture2D* GetTexture() const;

    UINT GetNumVertices() const;

  private:
    // disabled
    TestModel();
    TestModel(const TestModel& cpy);
    TestModel& operator=(const TestModel& cpy);

    /// <summary>
    /// Creates a test texture
    /// </summary>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="height">
    /// height of the texture in pixels
    /// </param>
    /// <param name="format">
    /// format of the pixels
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture(UINT& width, UINT& height, GraphicsDataFormat& format, std::vector<UINT8>& bytes);

    /// <summary>
    /// vertex buffer for the test case
    /// </summary>
    VertexBuffer_PositionTexture* m_verts;

    /// <summary>
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;

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
