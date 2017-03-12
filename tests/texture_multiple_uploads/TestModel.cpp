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
    { XMFLOAT3(-1.0f,-1.0f, 0.0f), XMFLOAT2(0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 0.0f), XMFLOAT2(1.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 0.0f), XMFLOAT2(1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT2(0.0f, 1.0f) },
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
    m_texture1d = Texture1DArray::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_LENGTH, (GraphicsDataFormat)TEXTURE_FORMAT);
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
    m_texture2d = Texture2DArray::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, TEXTURE_LENGTH, (GraphicsDataFormat)TEXTURE_FORMAT);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 2D:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the buffers for uploading the textures
  try
  {
    m_upload_texture.reserve(TEXTURE_MODE_MAX * TEXTURE_LENGTH);
    for (UINT i = 0; i < TEXTURE_LENGTH; i++)
    {
      m_upload_texture.push_back(TextureUploadBuffer::CreateD3D12(graphics, *m_texture1d));
    }
    for (UINT i = 0; i < TEXTURE_LENGTH; i++)
    {
      m_upload_texture.push_back(TextureUploadBuffer::CreateD3D12(graphics, *m_texture2d));
    }
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
    for (UINT16 i = 0; i < TEXTURE_LENGTH; i++)
    {
      vector<UINT8> tex_bytes;
      CreateTexture1D(i, tex_bytes);
      m_upload_texture[i]->PrepUpload(graphics, *command_list, *m_texture1d, i, tex_bytes);
    }
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
    for (UINT16 i = 0; i < TEXTURE_LENGTH; i++)
    {
      vector<UINT8> tex_bytes;
      CreateTexture2D(i, tex_bytes);
      m_upload_texture[TEXTURE_LENGTH + i]->PrepUpload(graphics, *command_list, *m_texture2d, i, tex_bytes);
    }
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
    command_list->Close();
    graphics.ExecuteCommandList(*command_list);
    graphics.WaitOnFence();
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload textures:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

TestModel::~TestModel()
{
  delete m_texture1d;
  delete m_texture2d;
  vector<TextureUploadBuffer*>::const_iterator upload_it = m_upload_texture.begin();
  while (upload_it != m_upload_texture.end())
  {
    delete *upload_it;
    ++upload_it;
  }
  delete m_indices;
  delete m_verts;
}

const VertexBuffer_PositionTexture* TestModel::GetVertexBuffer() const
{
  return m_verts;
}

const IndexBuffer16* TestModel::GetIndexBuffer() const
{
  return m_indices;
}

const Texture1DArray* TestModel::GetTexture() const
{
  return m_texture1d;
}

UINT TestModel::GetNumVertices() const
{
  return m_verts->GetNumVertices();
}

void TestModel::CreateTexture1D(UINT16 index, std::vector<UINT8>& bytes)
{
  UINT               width  = 64;
  GraphicsDataFormat format = R8B8G8A8_UNORM;

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT tex_size = width * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
  {
    const float percent   = x / (float)width;
    bytes[byte_index]     = (UINT8)(255 * (1 - percent));
    bytes[byte_index + 1] = (255 / (TEXTURE_LENGTH - 1)) * index;
    bytes[byte_index + 2] = (UINT8)(255 * percent);
    bytes[byte_index + 3] = 255;
  }
}

void TestModel::CreateTexture2D(UINT16 index, std::vector<UINT8>& bytes)
{
  UINT               width  = 64;
  UINT               height = 64;
  GraphicsDataFormat format = R8B8G8A8_UNORM;

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT tex_size = width * height * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT y = 0; y < height; y++)
  {
    for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
    {
      if (x <= y)
      {
        bytes[byte_index]     = 255;
        bytes[byte_index + 1] = (255 / (TEXTURE_LENGTH - 1)) * index;
        bytes[byte_index + 2] = 0;
        bytes[byte_index + 3] = 255;
      }
      else
      {
        bytes[byte_index]     = 0;
        bytes[byte_index + 1] = (255 / (TEXTURE_LENGTH - 1)) * index;
        bytes[byte_index + 2] = 255;
        bytes[byte_index + 3] = 255;
      }
    }
  }
}
