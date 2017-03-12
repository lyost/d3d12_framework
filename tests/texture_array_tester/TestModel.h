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

    const Texture1DArray* GetTexture() const;

    UINT GetNumVertices() const;

  private:
    // disabled
    TestModel();
    TestModel(const TestModel& cpy);
    TestModel& operator=(const TestModel& cpy);

    /// <summary>
    /// Creates a test 1D texture
    /// </summary>
    /// <param name="index">
    /// index of the texture in the array that the image is being created for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture1D(UINT16 index, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates a test 2D texture
    /// </summary>
    /// <param name="index">
    /// index of the texture in the array that the image is being created for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture2D(UINT16 index, std::vector<UINT8>& bytes);

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
    Texture1DArray* m_texture1d;

    /// <summary>
    /// texture
    /// </summary>
    Texture2DArray* m_texture2d;

    /// <summary>
    /// buffer for uploading the texture's data
    /// </summary>
    TextureUploadBuffer* m_upload_texture;
};

#endif /* TEST_MODEL_H */
