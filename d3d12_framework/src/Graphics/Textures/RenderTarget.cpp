#include "Graphics/Textures/RenderTarget.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTarget.h"

void RenderTarget::CreateD3D12(const GraphicsCore& graphics, const std::vector<Config>& configs, std::vector<RenderTarget*>& out)
{
  D3D12_RenderTarget::Create(graphics, configs, out);
}

RenderTarget::RenderTarget()
{
}

RenderTarget::~RenderTarget()
{
}
