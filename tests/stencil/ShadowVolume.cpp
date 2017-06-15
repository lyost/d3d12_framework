#include <sstream>
#include <directxmath.h>
#include "ShadowVolume.h"
#include "Graphics/VectorOps.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

ShadowVolume::ShadowVolume(GraphicsCore& graphics, DirectX::XMFLOAT3 light_pos, const Vertex_PositionTextureUVNormal* quad)
{
  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_PositionTextureUVNormal vertices[8];
  for (int i = 0; i < 4; i++)
  {
    vertices[i].pos = quad[i].pos;

    XMFLOAT3 dir = quad[i].pos - light_pos;
    XMVECTOR dir_tmp = XMLoadFloat3(&dir);
    XMVector3Normalize(dir_tmp);
    XMStoreFloat3(&dir, dir_tmp);
    vertices[i + 4].pos = quad[i].pos + (dir * SHADOW_LENGTH);
  }
  try
  {
    m_verts = VertexBuffer_PositionTextureUVNormal::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the index buffer
  WORD indices[] =
  {
    3, 1, 0,
    2, 1, 3,

    7, 0, 4,
    3, 0, 7,

    5, 1, 6,
    6, 1, 2,

    4, 5, 6,
    7, 4, 6,

    2, 3, 7,
    2, 7, 6,

    4, 0, 1,
    5, 4, 1,
  };
  try
  {
    m_indices = IndexBuffer16::CreateD3D12(graphics, ARRAYSIZE(indices), indices);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create index buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

ShadowVolume::~ShadowVolume()
{
  delete m_indices;
  delete m_verts;
}

const VertexBuffer_PositionTextureUVNormal* ShadowVolume::GetVertexBuffer() const
{
  return m_verts;
}

const IndexBuffer16* ShadowVolume::GetIndexBuffer() const
{
  return m_indices;
}
