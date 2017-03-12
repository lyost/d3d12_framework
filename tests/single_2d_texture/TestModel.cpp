#include <sstream>
#include <directxmath.h>
#include "TestModel.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

const UINT tex_width = 256;
const UINT tex_height = 256;

TestModel::TestModel(GraphicsCore& graphics, ShaderResourceDescHeap* shader_buffer_heap, CommandList* command_list)
{
  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_PositionTextureUV vertices[] =
  {
    { XMFLOAT3( 0.0f,   0.25f * aspect_ratio, 0.0f), XMFLOAT2(0.5f, 0.0f) },
    { XMFLOAT3( 0.25f, -0.25f * aspect_ratio, 0.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-0.25f, -0.25f * aspect_ratio, 0.0f), XMFLOAT2(0.0f, 1.0f) },
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

  // create the texture
  try
  {
    m_texture = Texture2D::CreateD3D12(graphics, *shader_buffer_heap, tex_width, tex_height, R8B8G8A8_UNORM);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_upload_texture = TextureUploadBuffer::CreateD3D12(graphics, *m_texture);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture upload buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  vector<UINT8> tex_bytes;
  CreateTextureImage(tex_bytes);
  try
  {
    m_upload_texture->PrepUpload(graphics, *command_list, *m_texture, tex_bytes);
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
  delete m_upload_texture;
  delete m_texture;
  delete m_verts;
}

const VertexBuffer_PositionTexture* TestModel::GetVertexBuffer() const
{
  return m_verts;
}

const Texture2D* TestModel::GetTexture() const
{
  return m_texture;
}

UINT TestModel::GetNumVertices() const
{
  return m_verts->GetNumVertices();
}

void TestModel::CreateTextureImage(std::vector<UINT8>& bytes) const
{
  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture
  const UINT tex_size = tex_width * tex_height * bytes_per_pixel;
  bytes.resize(tex_size);
  for (UINT byte_index = 0; byte_index < tex_size; byte_index += bytes_per_pixel)
  {
    bytes[byte_index] = 0;
    bytes[byte_index + 1] = 255;
    bytes[byte_index + 2] = 0;
    bytes[byte_index + 3] = 255;
  }
}
