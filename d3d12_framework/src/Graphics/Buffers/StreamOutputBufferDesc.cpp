#include "Graphics/Buffers/StreamOutputBufferDesc.h"

StreamOutputBufferDesc::StreamOutputBufferDesc(UINT stream,BYTE slot)
:m_stream(stream),
 m_slot(slot),
 m_stride(0)
{
}

StreamOutputBufferDesc::StreamOutputBufferDesc(
  const StreamOutputBufferDesc& cpy)
:m_stream(cpy.m_stream),
 m_slot(cpy.m_slot),
 m_sems(cpy.m_sems),
 m_stride(cpy.m_stride)
{
}

StreamOutputBufferDesc& StreamOutputBufferDesc::operator=(
  const StreamOutputBufferDesc& cpy)
{
  m_stream = cpy.m_stream;
  m_slot   = cpy.m_slot;
  m_sems   = cpy.m_sems;
  m_stride = cpy.m_stride;
  
  return *this;
}

StreamOutputBufferDesc::~StreamOutputBufferDesc()
{
}

void StreamOutputBufferDesc::AddSemantic(UINT size,Semantics semantic,
  UINT index,BYTE start,BYTE count)
{
  D3D11_SO_DECLARATION_ENTRY entry;
  entry.Stream         = m_stream;
  entry.SemanticName   = GetSemanticName(semantic);
  entry.SemanticIndex  = index;
  entry.StartComponent = start;
  entry.ComponentCount = count;
  entry.OutputSlot     = m_slot;
  
  m_sems.push_back(entry);
  m_stride += size;
}

UINT StreamOutputBufferDesc::GetStream() const
{
  return m_stream;
}

UINT StreamOutputBufferDesc::GetSlot() const
{
  return m_slot;
}

UINT StreamOutputBufferDesc::GetStride() const
{
  return m_stride;
}

const std::vector<D3D11_SO_DECLARATION_ENTRY>&
  StreamOutputBufferDesc::GetSemantics() const
{
  return m_sems;
}
