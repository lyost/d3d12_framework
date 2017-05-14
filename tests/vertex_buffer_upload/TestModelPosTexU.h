#ifndef TEST_MODEL_POS_TEX_U_H
#define TEST_MODEL_POS_TEX_U_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"

class TestModelPosTexU
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
    TestModelPosTexU(GraphicsCore& graphics, ShaderResourceDescHeap* shader_buffer_heap, CommandList& command_list);

    ~TestModelPosTexU();

    /// <summary>
    /// Preps the command list for uploading the initial or modified state to the vertex buffer.  The command list must execute followed by a fence for the transfer to be completed.
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
    const VertexBufferGPU_PositionTextureU* GetVertexBuffer() const;

    /// <summary>
    /// Retrieves the index buffer for the model
    /// </summary>
    /// <returns>
    /// index buffer
    /// </returns>
    const IndexBufferGPU16* GetIndexBuffer() const;

    /// <summary>
    /// Retrieves the first texture in the descriptor heap for the model
    /// </summary>
    /// <returns>
    /// model's first texture in the descriptor heap
    /// </returns>
    const Texture1D* GetTexture() const;

  private:
    // disabled
    TestModelPosTexU();
    TestModelPosTexU(const TestModelPosTexU& cpy);
    TestModelPosTexU& operator=(const TestModelPosTexU& cpy);

    /// <summary>
    /// Creates a test texture
    /// </summary>
    /// <param name="width">
    /// width of the texture in pixels
    /// </param>
    /// <param name="format">
    /// format of the pixels
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture(UINT& width, GraphicsDataFormat& format, std::vector<UINT8>& bytes);

    /// <summary>
    /// vertex buffer for the test case
    /// </summary>
    VertexBuffer_PositionTextureU* m_verts;

    /// <summary>
    /// GPU-only vertex buffer for the test case
    /// </summary>
    VertexBufferGPU_PositionTextureU* m_gpu_verts;

    /// <summary>
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;

    /// <summary>
    /// GPU-only index buffer for the test case
    /// </summary>
    IndexBufferGPU16* m_gpu_indices;

    /// <summary>
    /// texture
    /// </summary>
    Texture1D* m_texture;

    /// <summary>
    /// vertex buffer data
    /// </summary>
    Vertex_PositionTextureU m_vert_data[4];
};

#endif /* TEST_MODEL_POS_TEX_U_H */
