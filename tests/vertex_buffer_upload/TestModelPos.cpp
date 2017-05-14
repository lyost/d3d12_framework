#include <sstream>
#include <directxmath.h>
#include "TestModelPos.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

TestModelPos::TestModelPos(GraphicsCore& graphics, CommandList& command_list)
{
  // create the host vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  m_vert_data[0] = { XMFLOAT3(-4.0f, 2.0f, 1.0f) };
  m_vert_data[1] = { XMFLOAT3(-3.0f, 2.0f, 1.0f) };
  m_vert_data[2] = { XMFLOAT3(-3.0f, 3.0f, 1.0f) };
  m_vert_data[3] = { XMFLOAT3(-4.0f, 3.0f, 1.0f) };
  try
  {
    m_verts = VertexBuffer_Position::CreateD3D12(graphics, ARRAYSIZE(m_vert_data), m_vert_data);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create host vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the gpu vertex buffer
  try
  {
    m_gpu_verts = VertexBufferGPU_Position::CreateD3D12(graphics, m_verts->GetNumVertices());
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create GPU vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // upload to the GPU vertex buffer
  try
  {
    m_verts->PrepUpload(graphics, command_list, *m_gpu_verts);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload to GPU vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // create the index buffer
  WORD indices[] =
  {
    2, 1, 0,
    3, 2, 0
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

TestModelPos::~TestModelPos()
{
  delete m_indices;
  delete m_verts;
  delete m_gpu_verts;
}

void TestModelPos::UpdateVertexBuffer(GraphicsCore& graphics, bool initial, CommandList& command_list)
{
  if (initial)
  {
    m_vert_data[0] = { XMFLOAT3(-4.0f, 2.0f, 1.0f) };
    m_vert_data[1] = { XMFLOAT3(-3.0f, 2.0f, 1.0f) };
    m_vert_data[2] = { XMFLOAT3(-3.0f, 3.0f, 1.0f) };
    m_vert_data[3] = { XMFLOAT3(-4.0f, 3.0f, 1.0f) };
  }
  else
  {
    m_vert_data[0] = { XMFLOAT3(-3.0f, 2.0f, 1.0f) };
    m_vert_data[1] = { XMFLOAT3(-2.0f, 2.0f, 1.0f) };
    m_vert_data[2] = { XMFLOAT3(-2.0f, 3.0f, 1.0f) };
    m_vert_data[3] = { XMFLOAT3(-3.0f, 3.0f, 1.0f) };
  }
  try
  {
    m_verts->Upload(0, m_vert_data, ARRAYSIZE(m_vert_data));
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload to vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }

  // upload to the GPU vertex buffer
  try
  {
    m_verts->PrepUpload(graphics, command_list, *m_gpu_verts);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to upload to GPU vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

const VertexBufferGPU_Position* TestModelPos::GetVertexBuffer() const
{
  return m_gpu_verts;
}

const IndexBuffer16* TestModelPos::GetIndexBuffer() const
{
  return m_indices;
}
