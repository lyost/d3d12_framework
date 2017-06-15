#ifndef OCCLUDER_H
#define OCCLUDER_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"
#include "ShadowVolume.h"

class Occluder
{
  public:
    Occluder(GraphicsCore& graphics, DirectX::XMFLOAT3 light_pos, ShaderResourceDescHeap* shader_buffer_heap, CommandList* command_list);
    ~Occluder();

    /// <summary>
    /// Retrieves the vertex buffer for the model
    /// </summary>
    /// <returns>
    /// vertex buffer
    /// </returns>
    const VertexBuffer_PositionTextureUVNormal* GetVertexBuffer() const;

    /// <summary>
    /// Retrieves the index buffer for the model
    /// </summary>
    /// <returns>
    /// index buffer
    /// </returns>
    const IndexBuffer16* GetIndexBuffer() const;

    /// <summary>
    /// Retrieves the shadow volume
    /// </summary>
    /// <returns>
    /// shadow volume for the occluder
    /// </returns>
    const ShadowVolume* GetShadowVolume() const;

    /// <summary>
    /// Retrieves the first texture in the descriptor heap for the model
    /// </summary>
    /// <returns>
    /// model's first texture in the descriptor heap
    /// </returns>
    const Texture2D* GetTexture() const;

  private:
    // disabled
    Occluder();
    Occluder(const Occluder& cpy);
    Occluder& operator=(const Occluder& cpy);

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
    VertexBuffer_PositionTextureUVNormal* m_verts;

    /// <summary>
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;

    /// <summary>
    /// shadow volume created by the light and the occluder
    /// </summary>
    ShadowVolume* m_shadow_volume;

    /// <summary>
    /// texture
    /// </summary>
    Texture2D* m_texture;
};

#endif /* OCCLUDER_H */
