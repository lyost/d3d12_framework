#ifndef GRAPHICS_DATA_FORMAT_H
#define GRAPHICS_DATA_FORMAT_H

/// <summary>
/// Enum of the various graphics data formats
/// </summary>
/// <remarks>
/// Values must match up to the values used by DXGI_FORMAT
/// </remarks>
enum GraphicsDataFormat
{
  R32G32B32A32_FLOAT = 2,
  R32G32B32_FLOAT    = 6,
  R32G32_FLOAT       = 16,
  R8B8G8A8_UNORM     = 28,
  // todo: fill in the rest
};

#endif /* GRAPHICS_DATA_FORMAT_H */
