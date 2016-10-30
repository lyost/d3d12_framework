#include "Graphics/CommandList.h"
#include "private_inc/D3D12/D3D12_CommandList.h"

CommandList* CommandList::CreateD3D12Direct(const GraphicsCore& graphics, Pipeline* pipeline)
{
  return D3D12_CommandList::Create(graphics, pipeline);
}

CommandList::CommandList()
{
}

CommandList::~CommandList()
{
}