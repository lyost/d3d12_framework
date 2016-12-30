#ifndef TEXTURE_H
#define TEXTURE_H

/// <summary>
/// Base class for the various texture classes
/// </summary>
class Texture
{
  public:
    enum TextureType
    {
      TEXTURE_1D = 0,
      TEXTURE_2D,
      TEXTURE_3D,
      TEXTURE_1D_ARRAY,
      TEXTURE_2D_ARRAY,
      TEXTURE_2D_RENDER_TARGET
    };

    virtual ~Texture();

    /// <summary>
    /// Retrieves which type of texture the instance is
    /// </summary>
    /// <returns>
    /// id of the texture type
    /// </returns>
    virtual TextureType GetType() const = 0;
    
  protected:
    Texture();

  private:
    // disabled
    Texture(const Texture& cpy);
    Texture& operator=(const Texture& cpy);
};

#endif /* TEXTURE_H */
