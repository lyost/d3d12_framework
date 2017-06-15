#include <sstream>
#include <directxmath.h>
#include "Occluder.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

Occluder::Occluder(GraphicsCore& graphics, DirectX::XMFLOAT3 light_pos, ShaderResourceDescHeap* shader_buffer_heap, CommandList* command_list)
{
  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_PositionTextureUVNormal vertices[] =
  {
    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f, 1.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f, 1.0f) },
  };
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

  m_shadow_volume = new ShadowVolume(graphics, light_pos, vertices);

  // create the texture image
  UINT width;
  UINT height;
  GraphicsDataFormat format;
  vector<UINT8> tex_bytes;
  CreateTexture(width, height, format, tex_bytes);

  // create the texture
  try
  {
    m_texture = Texture2D::CreateD3D12(graphics, *shader_buffer_heap, width, height, format);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  TextureUploadBuffer* upload_texture;
  try
  {
    upload_texture = TextureUploadBuffer::CreateD3D12(graphics, *m_texture);
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
    command_list->Reset(NULL);
    upload_texture->PrepUpload(graphics, *command_list, *m_texture, tex_bytes);
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

  delete upload_texture;
}

Occluder::~Occluder()
{
  delete m_texture;
  delete m_shadow_volume;
  delete m_indices;
  delete m_verts;
}

const VertexBuffer_PositionTextureUVNormal* Occluder::GetVertexBuffer() const
{
  return m_verts;
}

const IndexBuffer16* Occluder::GetIndexBuffer() const
{
  return m_indices;
}

const ShadowVolume* Occluder::GetShadowVolume() const
{
  return m_shadow_volume;
}

const Texture2D* Occluder::GetTexture() const
{
  return m_texture;
}

void Occluder::CreateTexture(UINT& width, UINT& height, GraphicsDataFormat& format, std::vector<UINT8>& bytes)
{
  width  = 64;
  height = 64;
  format = R8B8G8A8_UNORM;
  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT tex_size = width * height * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT y = 0; y < height; y++)
  {
    for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
    {
      bytes[byte_index]     = 255;
      bytes[byte_index + 1] = 0;
      bytes[byte_index + 2] = 0;
      bytes[byte_index + 3] = 255;
    }
  }
}
