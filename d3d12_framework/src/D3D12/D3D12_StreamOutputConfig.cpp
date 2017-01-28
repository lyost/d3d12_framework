#include "private_inc/D3D12/D3D12_StreamOutputConfig.h"
#include "private_inc/D3D12/D3D12_Limits.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

D3D12_StreamOutputConfig::D3D12_StreamOutputConfig(UINT num_entries)
:m_num_entries(num_entries)
{
  m_entries = new D3D12_SO_DECLARATION_ENTRY[num_entries];

  m_strides = new UINT[MAX_OUTPUT_STREAMS];
  memset(m_strides, 0, sizeof(UINT) * MAX_OUTPUT_STREAMS);

  m_desc.pSODeclaration   = m_entries;
  m_desc.NumEntries       = num_entries;
  m_desc.pBufferStrides   = m_strides;
  m_desc.NumStrides       = MAX_OUTPUT_STREAMS;
  m_desc.RasterizedStream = 0;
}

D3D12_StreamOutputConfig::~D3D12_StreamOutputConfig()
{
  delete [] m_entries;
  delete [] m_strides;
}

void D3D12_StreamOutputConfig::SetStreamToRasterizer(UINT index)
{
  m_desc.RasterizedStream = index;
}

void D3D12_StreamOutputConfig::SetEntry(UINT entry_index, UINT stream_index, Semantics sem, UINT sem_index, BYTE start_component, BYTE num_components, BYTE output_slot, UINT stride)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (entry_index >= m_num_entries)
  {
    throw FrameworkException("entry_index beyond number of entries");
  }
  if (stream_index >= MAX_OUTPUT_STREAMS)
  {
    throw FrameworkException("stream_index beyond number of allowed output streams");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_entries[entry_index].Stream         = stream_index;
  m_entries[entry_index].SemanticName   = GetSemanticName(sem);
  m_entries[entry_index].SemanticIndex  = sem_index;
  m_entries[entry_index].StartComponent = start_component;
  m_entries[entry_index].ComponentCount = num_components;
  m_entries[entry_index].OutputSlot     = output_slot;

  m_strides[stream_index] += stride;
}

const D3D12_STREAM_OUTPUT_DESC& D3D12_StreamOutputConfig::GetDesc() const
{
  return m_desc;
}