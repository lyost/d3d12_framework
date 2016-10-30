#include "Graphics/InputLayout.h"
#include "private_inc/D3D12/D3D12_InputLayout.h"

InputLayout* InputLayout::CreateD3D12(UINT num)
{
  return new D3D12_InputLayout(num);
}

InputLayout::InputLayout()
{
}

InputLayout::~InputLayout()
{
}
