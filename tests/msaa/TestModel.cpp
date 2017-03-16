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
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 1.0f) },

    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT3(1.0f, 1.0f, 0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT3(1.0f, 0.0f, 1.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f), XMFLOAT3(1.0f, 1.0f, 1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },
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

  // create the textures
  try
  {
    m_texture1d = Texture1D::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, (GraphicsDataFormat)TEXTURE_FORMAT, NUM_MIPMAPS);
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
    m_texture2d = Texture2D::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, (GraphicsDataFormat)TEXTURE_FORMAT, NUM_MIPMAPS);
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
    m_texture3d = Texture3D::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, TEXTURE_DEPTH, (GraphicsDataFormat)TEXTURE_FORMAT, NUM_MIPMAPS);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 3D:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_texture1d_array = Texture1DArray::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, ARRAY_SIZE, (GraphicsDataFormat)TEXTURE_FORMAT, NUM_MIPMAPS);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 1D array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_texture2d_array = Texture2DArray::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, ARRAY_SIZE, (GraphicsDataFormat)TEXTURE_FORMAT, NUM_MIPMAPS);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture 2D array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_texture_cube = TextureCube::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, (GraphicsDataFormat)TEXTURE_FORMAT, NUM_MIPMAPS);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture cube:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
  try
  {
    m_texture_cube_array = TextureCubeArray::CreateD3D12(graphics, *shader_buffer_heap, TEXTURE_WIDTH, TEXTURE_HEIGHT, ARRAY_SIZE, (GraphicsDataFormat)TEXTURE_FORMAT, NUM_MIPMAPS);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create texture cube array:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // start uploading the texture
  try
  {
    m_upload_texture.reserve(TEXTURE_MODE_MAX * NUM_MIPMAPS);
    TextureUploadBuffer* buffer;

    for (UINT16 i = 0; i < NUM_MIPMAPS; i++)
    {
      vector<UINT8> tex_bytes;
      CreateTexture1D(i, tex_bytes);
      buffer = TextureUploadBuffer::CreateD3D12(graphics, *m_texture1d);
      buffer->PrepUpload(graphics, *command_list, *m_texture1d, tex_bytes, i);
      m_upload_texture.push_back(buffer);
    }
    for (UINT16 i = 0; i < NUM_MIPMAPS; i++)
    {
      vector<UINT8> tex_bytes;
      CreateTexture2D(i, tex_bytes);
      buffer = TextureUploadBuffer::CreateD3D12(graphics, *m_texture2d);
      buffer->PrepUpload(graphics, *command_list, *m_texture2d, tex_bytes, i);
      m_upload_texture.push_back(buffer);
    }
    for (UINT16 i = 0; i < NUM_MIPMAPS; i++)
    {
      vector<UINT8> tex_bytes;
      CreateTexture3D(i, tex_bytes);
      buffer = TextureUploadBuffer::CreateD3D12(graphics, *m_texture3d);
      buffer->PrepUpload(graphics, *command_list, *m_texture3d, tex_bytes, i);
      m_upload_texture.push_back(buffer);
    }
    for (UINT j = 0; j < ARRAY_SIZE; j++)
    {
      for (UINT16 i = 0; i < NUM_MIPMAPS; i++)
      {
        vector<UINT8> tex_bytes;
        CreateTexture1DArray(j, i, tex_bytes);
        buffer = TextureUploadBuffer::CreateD3D12(graphics, *m_texture1d_array);
        buffer->PrepUpload(graphics, *command_list, *m_texture1d_array, j, tex_bytes, i);
        m_upload_texture.push_back(buffer);
      }
    }
    for (UINT j = 0; j < ARRAY_SIZE; j++)
    {
      for (UINT16 i = 0; i < NUM_MIPMAPS; i++)
      {
        vector<UINT8> tex_bytes;
        CreateTexture2DArray(j, i, tex_bytes);
        buffer = TextureUploadBuffer::CreateD3D12(graphics, *m_texture2d_array);
        buffer->PrepUpload(graphics, *command_list, *m_texture2d_array, j, tex_bytes, i);
        m_upload_texture.push_back(buffer);
      }
    }
    for (UINT16 side = 0; side < TEXTURES_PER_CUBE; side++)
    {
      for (UINT16 i = 0; i < NUM_MIPMAPS; i++)
      {
        vector<UINT8> tex_bytes;
        CreateTextureCube(side, i, tex_bytes);
        buffer = TextureUploadBuffer::CreateD3D12(graphics, *m_texture_cube);
        buffer->PrepUpload(graphics, *command_list, *m_texture_cube, side, tex_bytes, i);
        m_upload_texture.push_back(buffer);
      }
    }
    for (UINT j = 0; j < ARRAY_SIZE; j++)
    {
      for (UINT16 side = 0; side < TEXTURES_PER_CUBE; side++)
      {
        for (UINT16 i = 0; i < NUM_MIPMAPS; i++)
        {
          vector<UINT8> tex_bytes;
          CreateTextureCubeArray(j, side, i, tex_bytes);
          buffer = TextureUploadBuffer::CreateD3D12(graphics, *m_texture_cube_array);
          buffer->PrepUpload(graphics, *command_list, *m_texture_cube_array, j, side, tex_bytes, i);
          m_upload_texture.push_back(buffer);
        }
      }
    }
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
}

TestModel::~TestModel()
{
  delete m_verts;
  delete m_indices;
  delete m_texture1d;
  delete m_texture2d;
  delete m_texture3d;
  delete m_texture1d_array;
  delete m_texture2d_array;
  delete m_texture_cube;
  delete m_texture_cube_array;
  vector<TextureUploadBuffer*>::const_iterator it = m_upload_texture.begin();
  while (it != m_upload_texture.end())
  {
    TextureUploadBuffer* buffer = *it;
    delete buffer;

    ++it;
  }
}

const VertexBuffer_PositionTexture* TestModel::GetVertexBuffer() const
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

void TestModel::CreateTexture1D(UINT16 mipmap, std::vector<UINT8>& bytes)
{
  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT width = TEXTURE_WIDTH >> mipmap;

  const UINT tex_size = width * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
  {
    const float percent = x / (float)width;

    bytes[byte_index]     = (UINT8)(255 * (1 - percent));
    bytes[byte_index + 1] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
    bytes[byte_index + 2] = (UINT8)(255 * percent);
    bytes[byte_index + 3] = 255;
  }
}

void TestModel::CreateTexture2D(UINT16 mipmap, std::vector<UINT8>& bytes)
{
  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT width  = TEXTURE_WIDTH  >> mipmap;
  const UINT height = TEXTURE_HEIGHT >> mipmap;

  const UINT center_x  = width / 2;
  const UINT center_y  = height / 2;
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
        bytes[byte_index]     = 0;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
        bytes[byte_index + 3] = 255;
      }
      else if (dy >= 0)
      {
        bytes[byte_index]     = 255;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
        bytes[byte_index + 3] = 255;
      }
      else if (dx < 0)
      {
        bytes[byte_index]     = 0;
        bytes[byte_index + 1] = 255;
        bytes[byte_index + 2] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
        bytes[byte_index + 3] = 255;
      }
      else
      {
        bytes[byte_index]     = 255;
        bytes[byte_index + 1] = 255;
        bytes[byte_index + 2] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
        bytes[byte_index + 3] = 255;
      }
    }
  }
}

void TestModel::CreateTexture3D(UINT16 mipmap, std::vector<UINT8>& bytes)
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
    { 255, 255, 255 },
    { 255,   0,   0 },
    {   0, 255,   0 },
    {   0,   0, 255 },
    { 255, 255,   0 },
    { 255,   0, 255 },
    {   0, 255, 255 },
    {   0,   0,   0 },
  };

  const UINT width  = TEXTURE_WIDTH  >> mipmap;
  const UINT height = TEXTURE_HEIGHT >> mipmap;
  const UINT depth  = TEXTURE_DEPTH  >> mipmap;

  const UINT tex_size = width * height * depth * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT z = 0; z < depth; z++)
  {
    for (UINT y = 0; y < height; y++)
    {
      for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
      {
        bytes[byte_index]     = colors[z].r;
        bytes[byte_index + 1] = colors[z].g;
        bytes[byte_index + 2] = colors[z].b;
        bytes[byte_index + 3] = 255;
      }
    }
  }
}

void TestModel::CreateTexture1DArray(UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes)
{
  static float multipliers[] = { 1, .5f };

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT width = TEXTURE_WIDTH >> mipmap;

  const UINT tex_size = width * bytes_per_pixel;
  bytes.resize(tex_size);
  UINT byte_index = 0;
  for (UINT x = 0; x < width; x++, byte_index += bytes_per_pixel)
  {
    const float percent = x / (float)width;

    bytes[byte_index]     = (UINT8)(255 * (1 - percent) * multipliers[index]);
    bytes[byte_index + 1] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
    bytes[byte_index + 2] = (UINT8)(255 * percent);
    bytes[byte_index + 3] = 255;
  }
}

void TestModel::CreateTexture2DArray(UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes)
{
  static float multipliers[] = { 1, .5f };

  const UINT bytes_per_pixel = 4; // 4 due to using a RGBA texture

  const UINT width  = TEXTURE_WIDTH >> mipmap;
  const UINT height = TEXTURE_HEIGHT >> mipmap;

  const UINT center_x  = width / 2;
  const UINT center_y  = height / 2;
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
        bytes[byte_index]     = 64 * index + 64;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
        bytes[byte_index + 3] = 255;
      }
      else if (dy >= 0)
      {
        bytes[byte_index]     = 255;
        bytes[byte_index + 1] = 0;
        bytes[byte_index + 2] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
        bytes[byte_index + 3] = 255;
      }
      else if (dx < 0)
      {
        bytes[byte_index]     = 0;
        bytes[byte_index + 1] = 255;
        bytes[byte_index + 2] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
        bytes[byte_index + 3] = 255;
      }
      else
      {
        bytes[byte_index]     = 255;
        bytes[byte_index + 1] = 255;
        bytes[byte_index + 2] = (UINT8)(255 * (mipmap / ((float)NUM_MIPMAPS - 1)));
        bytes[byte_index + 3] = 255;
      }
    }
  }
}

void TestModel::CreateTextureCube(UINT16 side, UINT16 mipmap, vector<UINT8>& bytes)
{
  static float multipliers[] = { 1, .5f };

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

  const UINT width  = TEXTURE_WIDTH >> mipmap;
  const UINT height = TEXTURE_HEIGHT >> mipmap;

  const UINT tex_size = width * height * bytes_per_pixel;
  bytes.resize(tex_size);
  for (UINT i = 0; i < tex_size; i += bytes_per_pixel)
  {
    bytes[i]     = (UINT8)(colors[side].r * multipliers[mipmap]);
    bytes[i + 1] = (UINT8)(colors[side].g * multipliers[mipmap]);
    bytes[i + 2] = (UINT8)(colors[side].b * multipliers[mipmap]);
    bytes[i + 3] = 255;
  }
}

void TestModel::CreateTextureCubeArray(UINT16 cube, UINT16 side, UINT16 mipmap, vector<UINT8>& bytes)
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

  static float multipliers[] = { 1, .5f };

  const UINT tex_size = TEXTURE_WIDTH * TEXTURE_HEIGHT * bytes_per_pixel;
  bytes.resize(tex_size);
  for (UINT i = 0; i < tex_size; i += bytes_per_pixel)
  {
    bytes[i]     = (UINT8)(colors[side].r * multipliers[cube] * multipliers[mipmap]);
    bytes[i + 1] = (UINT8)(colors[side].g * multipliers[cube] * multipliers[mipmap]);
    bytes[i + 2] = (UINT8)(colors[side].b * multipliers[cube] * multipliers[mipmap]);
    bytes[i + 3] = 255;
  }
}
