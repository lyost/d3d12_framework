#include <sstream>
#include <directxmath.h>
#include "TestModel.h"
#include "FrameworkException.h"
#include "log.h"
using namespace DirectX;
using namespace std;

TestModel::TestModel(GraphicsCore& graphics, ShaderResourceDescHeap* shader_buffer_heap, CommandList* command_list)
{
  // create the vertex buffer
  const Viewport& default_viewport = graphics.GetDefaultViewport();
  float aspect_ratio = default_viewport.width / default_viewport.height;
  // for topology IA_TOPOLOGY_TRIANGLE_LIST
  /*Vertex_Position vertices[] =
  {
    { XMFLOAT3(-1.5f, -1.5f, 0) },
    { XMFLOAT3(-1.5f,  1.5f, 0) },
    { XMFLOAT3( 1.5f, -1.5f, 0) },

    { XMFLOAT3(-1.5f,  1.5f, 0) },
    { XMFLOAT3( 1.5f,  1.5f, 0) },
    { XMFLOAT3( 1.5f, -1.5f, 0) },
  };*/
  // for topology IA_TOPOLOGY_TRIANGLE_STRIP
  Vertex_Position vertices[] =
  {
    { XMFLOAT3(-1.5f, -1.5f, 0) },
    { XMFLOAT3(-1.5f,  1.5f, 0) },
    { XMFLOAT3( 1.5f, -1.5f, 0) },
    { XMFLOAT3( 1.5f,  1.5f, 0) },
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
}

TestModel::~TestModel()
{
  delete m_verts;
}

const VertexBuffer_Position* TestModel::GetVertexBuffer() const
{
  return m_verts;
}
