#include <fstream>
#include "private_inc/D3D12/D3D12_Shader.h"
using namespace std;

D3D12_Shader* D3D12_Shader::Load(const char* path)
{
  ifstream in(path, ios_base::in | ios_base::binary);
  if (!in.good())
  {
    return NULL;
  }

  // get the file length, in bytes
  in.seekg(0, ios_base::end);
  streampos len = in.tellg();
  if (len > UINT_MAX)
  {
    // only handles files whose length fits into a UINT for now
    in.close();
    return NULL;
  }

  // load the file
  size_t length = (size_t)len;
  in.seekg(0, ios_base::beg);
  char* data = new char[length];
  if (!in.read(data, length))
  {
    delete [] data;
    in.close();
    return false;
  }

  in.close();
  return new D3D12_Shader(data, length);
}

D3D12_Shader::D3D12_Shader(const char* bytecode, size_t len)
{
  m_bytecode.pShaderBytecode = bytecode;
  m_bytecode.BytecodeLength = len;
}

D3D12_Shader::~D3D12_Shader()
{
  delete[] m_bytecode.pShaderBytecode;
}

const D3D12_SHADER_BYTECODE& D3D12_Shader::GetShader() const
{
  return m_bytecode;
}
