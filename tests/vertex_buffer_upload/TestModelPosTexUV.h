#ifndef TEST_MODEL_POS_TEX_UV_H
#define TEST_MODEL_POS_TEX_UV_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"

class TestModelPosTexUV
{
  public:
    /// <summary>
    /// Creates a test model.  The command list is executed internally.
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="shader_buffer_heap">
    /// descriptor heap for the texture
    /// </param>
    /// <param name="command_list">
    /// command list to write the upload commands to
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    TestModelPosTexUV(GraphicsCore& graphics, ShaderResourceDescHeap* shader_buffer_heap, CommandList& command_list);

    ~TestModelPosTexUV();

    /// <summary>
    /// Updates the vertex buffer to either its initial state or a modified state
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="initial">
    /// true if the vertex buffer should be updated to its initial false
    /// false for a modified state
    /// </param>
    /// <param name="command_list">
    /// command list to write the upload commands to
    /// </param>
    void UpdateVertexBuffer(GraphicsCore& graphics, bool initial, CommandList& command_list);

    /// <summary>
    /// Retrieves the vertex buffer for the model
    /// </summary>
    /// <returns>
    /// vertex buffer
    /// </returns>
    const VertexBufferGPU_PositionTextureUV* GetVertexBuffer() const;

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
    VertexBuffer_PositionTextureUV* m_verts;

    /// <summary>
    /// GPU-only vertex buffer for the test case
    /// </summary>
    VertexBufferGPU_PositionTextureUV* m_gpu_verts;

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
