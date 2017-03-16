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
  Vertex_PositionColor vertices[] =
  {
    { XMFLOAT3( 0.0f,   0.25f * aspect_ratio, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f) },
    { XMFLOAT3( 0.25f, -0.25f * aspect_ratio, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f) },
    { XMFLOAT3(-0.25f, -0.25f * aspect_ratio, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f) },
  };
  try
  {
    m_verts = VertexBuffer_PositionColor::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
  }
  catch (const FrameworkException& err)
  {
    ostringstream out;
    out << "Unable to create vertex buffer:\n" << err.what();
    log_print(out.str().c_str());
    exit(1);
  }
}

TestModel::~TestModel()
{
  delete m_verts;
}

const VertexBuffer_PositionColor* TestModel::GetVertexBuffer() const
{
  return m_verts;
}
