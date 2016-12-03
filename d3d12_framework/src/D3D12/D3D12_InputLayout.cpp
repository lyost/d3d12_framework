#include "private_inc/D3D12/D3D12_InputLayout.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

D3D12_InputLayout::D3D12_InputLayout(UINT num)
:m_num(num),
 m_next(0)
{
  m_layout = new D3D12_INPUT_ELEMENT_DESC[num];
}

D3D12_InputLayout::~D3D12_InputLayout()
{
  delete m_layout;
}

void D3D12_InputLayout::SetNextElement(Semantics semantic,UINT index, GraphicsDataFormat format, UINT input_slot, bool instance, UINT step_rate)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (m_next >= m_num)
  {
    throw FrameworkException("No more input layout slots available");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */
  
  m_layout[m_next].SemanticName           = GetSemanticName(semantic);
  m_layout[m_next].SemanticIndex          = index;
  m_layout[m_next].Format                 = (DXGI_FORMAT)format;
  m_layout[m_next].AlignedByteOffset      = D3D12_APPEND_ALIGNED_ELEMENT;
  m_layout[m_next].InputSlot              = input_slot;
  
  if (instance)
  {
    m_layout[m_next].InputSlotClass       = D3D12_INPUT_CLASSIFICATION_PER_INSTANCE_DATA;
    m_layout[m_next].InstanceDataStepRate = step_rate;
  }
  else
  {
    m_layout[m_next].InputSlotClass       = D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA;
    m_layout[m_next].InstanceDataStepRate = 0;
  }
  
  ++m_next;
}

UINT D3D12_InputLayout::GetNum() const
{
  return m_num;
}

UINT D3D12_InputLayout::GetNextIndex() const
{
  return m_next;
}

const D3D12_INPUT_ELEMENT_DESC* D3D12_InputLayout::GetLayout() const
{
  return m_layout;
}
