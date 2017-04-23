#ifndef TEST_MODEL_POS_TEX_UVW_H
#define TEST_MODEL_POS_TEX_UVW_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"

class TestModelPosTexUVW
{
  public:
    TestModelPosTexUVW(GraphicsCore& graphics, ShaderResourceDescHeap* shader_buffer_heap, CommandList* command_list);
    ~TestModelPosTexUVW();

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
    const Texture3D* GetTexture() const;

  private:
    // disabled
    TestModelPosTexUVW();
    TestModelPosTexUVW(const TestModelPosTexUVW& cpy);
    TestModelPosTexUVW& operator=(const TestModelPosTexUVW& cpy);

    /// <summary>
    /// Creates a test texture
    /// </summary>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="height">
    /// height of the texture in pixels
    /// </param>
    /// <param name="depth">
    /// depth of the texture in pixels
    /// </param>
    /// <param name="format">
    /// format of the pixels
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture(UINT& width, UINT& height, UINT16& depth, GraphicsDataFormat& format, std::vector<UINT8>& bytes);

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
    Texture3D* m_texture;

    /// <summary>
    /// vertex buffer data
    /// </summary>
    Vertex_PositionTextureUVW m_vert_data[4];
};

#endif /* TEST_MODEL_POS_TEX_UVW_H */
