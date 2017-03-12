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

    const Texture1D* GetTexture() const;

    UINT GetNumVertices() const;

  private:
    // disabled
    TestModel();
    TestModel(const TestModel& cpy);
    TestModel& operator=(const TestModel& cpy);

    /// <summary>
    /// Creates a test 1D texture
    /// </summary>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture1D(UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates a test 2D texture
    /// </summary>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture2D(UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates a test 3D texture
    /// </summary>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture3D(UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates a test 1D texture for the 2D texture array
    /// </summary>
    /// <param name="index">
    /// index into the texture array for which texture to create
    /// </param>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture1DArray(UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates a test 2D texture for the 2D texture array
    /// </summary>
    /// <param name="index">
    /// index into the texture array for which texture to create
    /// </param>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture2DArray(UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates textures for the texture cube
    /// </summary>
    /// <param name="indes">
    /// index of which side to create the texture for
    /// </param>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTextureCube(UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates textures for the texture cube array
    /// </summary>
    /// <param name="cube">
    /// index of which cube to create the textures for
    /// </param>
    /// <param name="index">
    /// index of which side to create the texture for
    /// </param>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTextureCubeArray(UINT16 cube, UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes);

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
    Texture1D* m_texture1d;

    /// <summary>
    /// texture
    /// </summary>
    Texture2D* m_texture2d;

    /// <summary>
    /// texture
    /// </summary>
    Texture3D* m_texture3d;

    /// <summary>
    /// texture
    /// </summary>
    Texture1DArray* m_texture1d_array;

    /// <summary>
    /// texture
    /// </summary>
    Texture2DArray* m_texture2d_array;

    /// <summary>
    /// texture
    /// </summary>
    TextureCube* m_texture_cube;

    /// <summary>
    /// texture
    /// </summary>
    TextureCubeArray* m_texture_cube_array;

    /// <summary>
    /// buffer for uploading the texture's data
    /// </summary>
    std::vector<TextureUploadBuffer*> m_upload_texture;
};

#endif /* TEST_MODEL_H */
