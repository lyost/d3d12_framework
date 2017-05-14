#include "private_inc/D3D12/Buffers/D3D12_VertexBufferArray.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_Custom.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_Position.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTextureU.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTextureUV.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionTextureUVW.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBuffer_PositionColor.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_Custom.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_Position.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionTextureU.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionTextureUV.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionTextureUVW.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferGPU_PositionColor.h"
#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBuffer.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

D3D12_VertexBufferArray::D3D12_VertexBufferArray(UINT num_buffers)
:m_num(num_buffers)
{
  m_vertex_buffers = new D3D12_VERTEX_BUFFER_VIEW[m_num];
  memset(m_vertex_buffers, 0, sizeof(D3D12_VERTEX_BUFFER_VIEW) * m_num);
}

D3D12_VertexBufferArray::~D3D12_VertexBufferArray()
{
  delete [] m_vertex_buffers;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBuffer_Custom& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBuffer_Custom& vertex_buffer = (const D3D12_VertexBuffer_Custom&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBuffer_Position& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBuffer_Position& vertex_buffer = (const D3D12_VertexBuffer_Position&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBuffer_PositionTextureU& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBuffer_PositionTextureU& vertex_buffer = (const D3D12_VertexBuffer_PositionTextureU&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBuffer_PositionTextureUV& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBuffer_PositionTextureUV& vertex_buffer = (const D3D12_VertexBuffer_PositionTextureUV&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBuffer_PositionTextureUVW& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBuffer_PositionTextureUVW& vertex_buffer = (const D3D12_VertexBuffer_PositionTextureUVW&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBuffer_PositionColor& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBuffer_PositionColor& vertex_buffer = (const D3D12_VertexBuffer_PositionColor&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBufferGPU_Custom& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBufferGPU_Custom& vertex_buffer = (const D3D12_VertexBufferGPU_Custom&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBufferGPU_Position& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBufferGPU_Position& vertex_buffer = (const D3D12_VertexBufferGPU_Position&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBufferGPU_PositionTextureU& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBufferGPU_PositionTextureU& vertex_buffer = (const D3D12_VertexBufferGPU_PositionTextureU&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBufferGPU_PositionTextureUV& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBufferGPU_PositionTextureUV& vertex_buffer = (const D3D12_VertexBufferGPU_PositionTextureUV&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBufferGPU_PositionTextureUVW& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBufferGPU_PositionTextureUVW& vertex_buffer = (const D3D12_VertexBufferGPU_PositionTextureUVW&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const VertexBufferGPU_PositionColor& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VertexBufferGPU_PositionColor& vertex_buffer = (const D3D12_VertexBufferGPU_PositionColor&)buffer;

  m_vertex_buffers[index] = vertex_buffer.m_view;
}

void D3D12_VertexBufferArray::Set(UINT index, const StreamOutputBuffer& buffer)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_StreamOutputBuffer& so_buffer = (const D3D12_StreamOutputBuffer&)buffer;

  m_vertex_buffers[index] = so_buffer.GetVertexBufferView();
}

void D3D12_VertexBufferArray::Clear(UINT index)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_num)
  {
    throw FrameworkException("index beyond number of vertex buffers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_vertex_buffers[index].BufferLocation = 0;
  m_vertex_buffers[index].SizeInBytes    = 0;
  m_vertex_buffers[index].StrideInBytes  = 0;
}

UINT D3D12_VertexBufferArray::GetNumBuffers() const
{
  return m_num;
}

const D3D12_VERTEX_BUFFER_VIEW* D3D12_VertexBufferArray::GetArray() const
{
  return m_vertex_buffers;
}
