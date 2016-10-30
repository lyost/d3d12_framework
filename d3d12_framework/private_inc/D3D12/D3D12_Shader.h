#ifndef D3D12_SHADER_H
#define D3D12_SHADER_H

#include <d3d12.h>
#include "Graphics/Shader.h"

class D3D12_Shader : public Shader
{
  public:
    /// <summary>
    /// Loads a D3D12 shader from the specified file
    /// </summary>
    /// <param name="path">
    /// path to the file to load
    /// </param>
    /// <returns>
    /// pointer to the Shader instance on success
    /// NULL on error
    /// </returns>
    static D3D12_Shader* Load(const char* path);

    ~D3D12_Shader();

    const D3D12_SHADER_BYTECODE& GetShader() const;

  private:
    // disabled
    D3D12_Shader(const D3D12_Shader& cpy);
    D3D12_Shader& operator= (const D3D12_Shader& cpy);

    D3D12_Shader(const char* bytecode, size_t len);

    /// <summary>
    /// byte code data for the shader
    /// </summary>
    D3D12_SHADER_BYTECODE m_bytecode;
};

#endif /* D3D12_SHADER_H */