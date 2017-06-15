#ifndef SHADOW_VOLUME_H
#define SHADOW_VOLUME_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Textures/TextureUploadBuffer.h"

class ShadowVolume
{
  public:
    /// <summary>
    /// Creates shadow volume
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="light_pos">
    /// position of the light source in world space
    /// </param>
    /// <param name="quad">
    /// world space vertex positions of a quad representing an occluder
    /// </param>
    ShadowVolume(GraphicsCore& graphics, DirectX::XMFLOAT3 light_pos, const Vertex_PositionTextureUVNormal* quad);

    ~ShadowVolume();

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

  private:
    // disabled
    ShadowVolume();
    ShadowVolume(const ShadowVolume& cpy);
    ShadowVolume& operator=(const ShadowVolume& cpy);

    enum
    {
      SHADOW_LENGTH = 10,
    };

    /// <summary>
    /// vertex buffer for the test case (note: using VertexBuffer_PositionTextureUVNormal here despite only position being needed to avoid having to create a new input layout/pipeline)
    /// </summary>
    VertexBuffer_PositionTextureUVNormal* m_verts;

    /// <summary>
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;
};

#endif /* SHADOW_VOLUME_H */
