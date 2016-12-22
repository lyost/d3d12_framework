#include <sstream>
#include "private_inc/D3D12/D3D12_CommandListBundle.h"
#include "private_inc/D3D12/D3D12_CommandList.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

D3D12_CommandListBundle* D3D12_CommandListBundle::Create()
{
  return new D3D12_CommandListBundle();
}

D3D12_CommandListBundle::D3D12_CommandListBundle()
{
}

D3D12_CommandListBundle::~D3D12_CommandListBundle()
{
  vector<ID3D12GraphicsCommandList*>::iterator it = m_lists.begin();
  while (it != m_lists.end())
  {
    ID3D12GraphicsCommandList* list = *it;
    list->Release();

    ++it;
  }
}

void D3D12_CommandListBundle::AddCommandList(const CommandList& list)
{
  ID3D12GraphicsCommandList* command_list = ((const D3D12_CommandList&)list).GetCommandList();
  command_list->AddRef();
  m_lists.push_back(command_list);

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (m_lists.size() > UINT_MAX)
  {
    ostringstream out;
    out << "Too many command lists now present in bundle.  Max " << UINT_MAX;
    throw FrameworkException(out.str());
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */
}

void D3D12_CommandListBundle::RemoveCommandList(const CommandList& list)
{
  ID3D12GraphicsCommandList* command_list = ((const D3D12_CommandList&)list).GetCommandList();
  vector<ID3D12GraphicsCommandList*>::iterator it = m_lists.begin();
  while (it != m_lists.end())
  {
    ID3D12GraphicsCommandList* list = *it;
    if (list == command_list)
    {
      list->Release();
      (*it) = NULL;
      break;
    }

    ++it;
  }
  // todo: is compressing the array over the now null element needed?
}

void D3D12_CommandListBundle::RemoveCommandList(UINT index)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_lists.size())
  {
    throw FrameworkException("index beyond number of command lists");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_lists[index]->Release();
  m_lists[index] = NULL;
  // todo: is compressing the array over the now null element needed?
}

UINT D3D12_CommandListBundle::GetNumCommandLists() const
{
  return (UINT)m_lists.size();
}

ID3D12GraphicsCommandList*const* D3D12_CommandListBundle::GetCommandLists() const
{
  return &(m_lists[0]);
}
