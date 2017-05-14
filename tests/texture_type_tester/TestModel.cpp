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
  Vertex_PositionTextureUVW vertices[] =
  {
    { XMFLOAT3(-1.0f,-1.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 0.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
  };
  try
  {
    m_verts = VertexBuffer_PositionTextureUVW::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
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

  // create the textures
  try
  {
    m_texture1d = Texture1D::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, (GraphicsDataFormat)TEXTURE_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 1D:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_texture2d = Texture2D::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, (GraphicsDataFormat)TEXTURE_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 2D:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_texture3d = Texture3D::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, TEXTURE_DEPTH, (GraphicsDataFormat)TEXTURE_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 3D:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the buffer for uploading the textures (will reuse the same buffer, so pick the largest texture)
  TextureUploadBuffer* upload_texture;
  try
  {
    upload_texture = TextureUploadBuffer::CreateD3D12(graphics, *m_texture3d);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture upload buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // upload the textures
  try
  {
    vector<UINT8> tex_bytes;
    CreateTexture1D(tex_bytes);
    upload_texture->PrepUpload(graphics, *command_list, *m_texture1d, tex_bytes);
    command_list->Close();
    graphics.ExecuteCommandList(*command_list);
    graphics.WaitOnFence();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    vector<UINT8> tex_bytes;
    CreateTexture2D(tex_bytes);
    command_list->Reset(NULL);
    upload_texture->PrepUpload(graphics, *command_list, *m_texture2d, tex_bytes);
    command_list->Close();
    graphics.ExecuteCommandList(*command_list);
    graphics.WaitOnFence();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    vector<UINT8> tex_bytes;
    CreateTexture3D(tex_bytes);
    command_list->Reset(NULL);
    upload_texture->PrepUpload(graphics, *command_list, *m_texture3d, tex_bytes);
    command_list->Close();
    graphics.ExecuteCommandList(*command_list);
    graphics.WaitOnFence();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload texture:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  delete upload_texture;
}

TestModel::~TestModel()
{
  delete m_texture1d;
  delete m_texture2d;
  delete m_texture3d;
  delete m_indices;
  delete m_verts;
}

const VertexBuffer_PositionTextureUVW* TestModel::GetVertexBuffer() const
{
  return m_verts;
}

const IndexBuffer16* TestModel::GetIndexBuffer() const
{
  return m_indices;
}

const Texture1D* TestModel::GetTexture() const
{
  return m_texture1d;
}

void TestModel::CreateTexture1D(std::vector<UINT8>& bytes)
{
  UINT               width  = 64;
  GraphicsDataFormat format = R8B8G8A8_UNORM;

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT tex_size = width * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
  {
    const float percent = x / (float)width;
    bytes[byte_index] = (UINT8)(255 * (1 - percent));
    bytes[byte_index + 1] = 0;
    bytes[byte_index + 2] = (UINT8)(255 * percent);
    bytes[byte_index + 3] = 255;
  }
}

void TestModel::CreateTexture2D(std::vector<UINT8>& bytes)
{
  UINT               width  = 64;
  UINT               height = 64;
  GraphicsDataFormat format = R8B8G8A8_UNORM;

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT center_x = width / 2;
  const UINT center_y = height / 2;
  const UINT radius_sq = center_x * center_x;

  const UINT tex_size = width * height * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT y = 0; y < height; y++)
  {
    for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
    {
      const float dx = x + .5f - center_x;
      const float dy = y + .5f - center_y;
      const float dist_sq = dx * dx + dy * dy;

      if (dist_sq > radius_sq)
      {
        bytes[byte_index] = 0;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = 0;
        bytes[byte_index + 3] = 255;
      }
      else if (dy >= 0)
      {
        bytes[byte_index] = 255;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = 0;
        bytes[byte_index + 3] = 255;
      }
      else if (dx < 0)
      {
        bytes[byte_index] = 0;
        bytes[byte_index + 1] = 255;
        bytes[byte_index + 2] = 0;
        bytes[byte_index + 3] = 255;
      }
      else
      {
        bytes[byte_index] = 0;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = 255;
        bytes[byte_index + 3] = 255;
      }
    }
  }
}

void TestModel::CreateTexture3D(std::vector<UINT8>& bytes)
{
  UINT               width  = 64;
  UINT               height = 64;
  UINT16             depth  = 3;
  GraphicsDataFormat format = R8B8G8A8_UNORM;

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT center_x = width / 2;
  const UINT center_y = height / 2;
  const UINT radius_sq = center_x * center_x;

  const UINT tex_size = width * height * depth * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT z = 0; z < depth; z++)
  {
    for (UINT y = 0; y < height; y++)
    {
      for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
      {
        bytes[byte_index]     = (z == 0) ? 255 : 0;
        bytes[byte_index + 1] = (z == 1) ? 255 : 0;
        bytes[byte_index + 2] = (z == 2) ? 255 : 0;
        bytes[byte_index + 3] = 255;
      }
    }
  }
}
