#include <sstream>
#include <directxmath.h>
#include "TestModel.h"
#include "TestTextureEnums.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

TestModel::TestModel(GraphicsCore& graphics, ShaderResourceDescHeap* shader_buffer_heap, CommandList* command_list)
{
  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_PositionTextureUV vertices[] =
  {
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3 (1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3(1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3(1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT2(0.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
  };
  try
  {
    m_verts = VertexBuffer_PositionTexture::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
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

    6, 4, 5,
    7, 4, 6,

    11, 9, 8,
    10, 9, 11,

    14, 12, 13,
    15, 12, 14,

    19, 17, 16,
    18, 17, 19,

    22, 20, 21,
    23, 20, 22
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

  // create the texture
  try
  {
    m_texture = Texture2DRenderTarget::CreateD3D12(graphics, *shader_buffer_heap, RTV_TEX_WIDTH, RTV_TEX_HEIGHT, (GraphicsDataFormat)RTV_TEX_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture to copy render target to:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

TestModel::~TestModel()
{
  delete m_verts;
  delete m_indices;
  delete m_texture;
}

const VertexBuffer_PositionTexture* TestModel::GetVertexBuffer() const
{
  return m_verts;
}

const IndexBuffer16* TestModel::GetIndexBuffer() const
{
  return m_indices;
}

Texture2DRenderTarget* TestModel::GetTexture() const
{
  return m_texture;
}
