#include <sstream>
#include <directxmath.h>
#include "TestModel.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

TestModel::TestModel(GraphicsCore& graphics)
{
  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  Vertex_Position vertices[] =
  {
    { XMFLOAT3(-3.0f, -3.0f, 0) },
    { XMFLOAT3( 3.0f, -3.0f, 0) },
    { XMFLOAT3( 3.0f,  3.0f, 0) },
    { XMFLOAT3(-3.0f,  3.0f, 0) },
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
    0, 1, 2, 3,
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

TestModel::~TestModel()
{
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
