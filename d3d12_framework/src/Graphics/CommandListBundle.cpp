#include "Graphics/CommandListBundle.h"
#include "private_inc/D3D12/D3D12_CommandListBundle.h"

CommandListBundle* CommandListBundle::CreateD3D12()
{
  return D3D12_CommandListBundle::Create();
}

CommandListBundle::CommandListBundle()
{
}

CommandListBundle::~CommandListBundle()
{
}
