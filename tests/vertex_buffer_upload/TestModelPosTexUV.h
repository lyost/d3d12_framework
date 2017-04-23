#ifndef TEST_MODEL_POS_TEX_UV_H
#define TEST_MODEL_POS_TEX_UV_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"

class TestModelPosTexUV
{
  public:
    TestModelPosTexUV(GraphicsCore& graphics, ShaderResourceDescHeap* shader_buffer_heap, CommandList* command_list);
    ~TestModelPosTexUV();

    /// <summary>
    /// Updates the vertex buffer to either its initial state or a modified state
    /// </summary>
    /// <param name="initial">
    /// true if the vertex buffer should be updated to its initial false
    /// false for a modified state
    /// </param?
    void UpdateVertexBuffer(bool initial);

    /// <summary>
    /// Retrieves the vertex buffer for the model
    /// </summary>
    /// <returns>
    /// vertex buffer
    /// </returns>
    const VertexBuffer_PositionTexture* GetVertexBuffer() const;

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
    const Texture2D* GetTexture() const;

  private:
    // disabled
    TestModelPosTexUV();
    TestModelPosTexUV(const TestModelPosTexUV& cpy);
    TestModelPosTexUV& operator=(const TestModelPosTexUV& cpy);

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
    /// vertex buffer data
    /// </summary>
    Vertex_PositionTextureUV m_vert_data[4];
};

#endif /* TEST_MODEL_POS_TEX_UV_H */
