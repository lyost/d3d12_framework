#include "Graphics/Shader.h"
#include "private_inc/D3D12/D3D12_Shader.h"

Shader* Shader::LoadD3D12(const char* path)
{
  return D3D12_Shader::Load(path);
}

Shader::Shader()
{
}

Shader::~Shader()
{
}
