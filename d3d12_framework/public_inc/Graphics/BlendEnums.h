#ifndef BLEND_ENUMS_H
#define BLEND_ENUMS_H

/// <summary>
/// Enum of the various blend modes
/// </summary>
/// <remarks>
/// Values must match D3D12_BLEND
/// </remarks>
enum BlendModes
{
  BLEND_MODE_ZERO = 1,
  BLEND_MODE_ONE,
  BLEND_MODE_SRC_COLOR,
  BLEND_MODE_INV_SRC_COLOR,
  BLEND_MODE_SRC_ALPHA,
  BLEND_MODE_INV_SRC_ALPHA,
  BLEND_MODE_DEST_ALPHA,
  BLEND_MODE_INV_DEST_ALPHA,
  BLEND_MODE_DEST_COLOR,
  BLEND_MODE_INV_DEST_COLOR,
  BLEND_MODE_SRC_ALPHA_SAT,
  BLEND_MODE_BLEND_FACTOR = 14,
  BLEND_MODE_INV_BLEND_FACTOR,
  BLEND_MODE_SRC1_COLOR,
  BLEND_MODE_INV_SRC1_COLOR,
  BLEND_MODE_SRC1_ALPHA,
  BLEND_MODE_INV_SRC1_ALPHA
};

/// <summary>
/// Enum of the various blend operations
/// </summary>
/// <remarks>
/// Values must match D3D12_BLEND_OP
/// </remarks>
enum BlendOp
{
  BLEND_OP_ADD,
  BLEND_OP_SUBTRACT,
  BLEND_OP_REV_SUBTRACT,
  BLEND_OP_MIN,
  BLEND_OP_MAX
};

/// <summary>
/// Enum of the various color write modes for blending
/// </summary>
/// <remarks>
/// Values must match D3D12_COLOR_WRITE_ENABLE
/// </remarks>
enum COLOR_WRITE_MODE
{
  COLOR_WRITE_RED   = 1,
  COLOR_WRITE_GREEN = 2,
  COLOR_WRITE_BLUE  = 4,
  COLOR_WRITE_ALPHA = 8,
  COLOR_WRITE_ALL   = COLOR_WRITE_RED | COLOR_WRITE_GREEN | COLOR_WRITE_BLUE | COLOR_WRITE_ALPHA
};

#endif /* BLEND_ENUMS_H */
