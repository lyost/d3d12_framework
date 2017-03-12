#ifndef TEST_TEXTURE_ENUMS_H
#define TEST_TEXTURE_ENUMS_H

enum TextureModes
{
  TEXTURE_MODE_1D = 0,
  TEXTURE_MODE_2D,
  TEXTURE_MODE_MAX
};

enum TextureProperties
{
  TEXTURE_WIDTH  = 64,
  TEXTURE_HEIGHT = 64,
  TEXTURE_LENGTH = 3,
  TEXTURE_FORMAT = R8B8G8A8_UNORM
};

#endif /* TEST_TEXTURE_ENUMS_H */
