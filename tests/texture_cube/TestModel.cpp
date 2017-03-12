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
  // create the vertex buffer (the position doubles as the uvw coordinates in this case since they are for a unit cube)
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_Position vertices[] =
  {
    { XMFLOAT3(-1.0f, 1.0f,-1.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f) },
    { XMFLOAT3(-1.0f,-1.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f) },
    { XMFLOAT3(-1.0f,-1.0f,-1.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f) },

    { XMFLOAT3( 1.0f,-1.0f, 1.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f) },
  };
  try
  {
    m_verts = VertexBuffer_Position::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
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
    m_texture = TextureCube::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, (GraphicsDataFormat)TEXTURE_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the buffers for uploading the textures
  try
  {
    m_upload_texture.reserve(TEXTURES_PER_CUBE);
    for (UINT i = 0; i < TEXTURES_PER_CUBE; i++)
    {
      m_upload_texture.push_back(TextureUploadBuffer::CreateD3D12(graphics, *m_texture));
    }
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture upload buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // start uploading the texture
  try
  {
    for (UINT16 i = 0; i < TEXTURES_PER_CUBE; i++)
    {
      vector<UINT8> tex_bytes;
      CreateTexture(i, tex_bytes);
      m_upload_texture[i]->PrepUpload(graphics, *command_list, *m_texture, i, tex_bytes);
    }
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // finish uploading the textures
  try
  {
    command_list->Close();
    graphics.ExecuteCommandList(*command_list);
    graphics.WaitOnFence();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to finish uploading textures:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

TestModel::~TestModel()
{
  delete m_texture;
  vector<TextureUploadBuffer*>::const_iterator upload_it = m_upload_texture.begin();
  while (upload_it != m_upload_texture.end())
  {
    delete *upload_it;
    ++upload_it;
  }
  delete m_indices;
  delete m_verts;
}

const VertexBuffer_Position* TestModel::GetVertexBuffer() const
{
  return m_verts;
}

const IndexBuffer16* TestModel::GetIndexBuffer() const
{
  return m_indices;
}

const TextureCube* TestModel::GetTexture() const
{
  return m_texture;
}

UINT TestModel::GetNumVertices() const
{
  return m_verts->GetNumVertices();
}

void TestModel::CreateTexture(UINT16 side, vector<UINT8>& bytes)
{
  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  struct Color
  {
    UINT8 r;
    UINT8 g;
    UINT8 b;
  };
  static Color colors[] =
  {
    { 255,   0,   0 },
    {   0, 255,   0 },
    {   0,   0, 255 },
    { 255, 255,   0 },
    { 255,   0, 255 },
    {   0, 255, 255 },
  };

  const UINT tex_size = TEXTURE_WIDTH * TEXTURE_HEIGHT * bytes_per_pixel;
  bytes.resize(tex_size);
  for (UINT i = 0; i < tex_size; i += bytes_per_pixel)
  {
    bytes[i]     = colors[side].r;
    bytes[i + 1] = colors[side].g;
    bytes[i + 2] = colors[side].b;
    bytes[i + 3] = 255;
  }
}
