#ifndef SHADER_H
#define SHADER_H

class Shader
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
    static Shader* LoadD3D12(const char* path);

    virtual ~Shader();

  protected:
    Shader();

  private:
    // disabled
    Shader(const Shader& cpy);
    Shader& operator= (const Shader& cpy);
};

#endif /* SHADER_H */