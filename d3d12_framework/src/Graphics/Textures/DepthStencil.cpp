#include "Graphics/Textures/DepthStencil.h"
#include "private_inc/D3D12/Textures/D3D12_DepthStencil.h"

void DepthStencil::CreateD3D12(const GraphicsCore& graphics, const std::vector<Config>& configs, std::vector<DepthStencil*>& out)
{
  D3D12_DepthStencil::Create(graphics, configs, out);
}

DepthStencil::DepthStencil()
{
}

DepthStencil::~DepthStencil()
{
}