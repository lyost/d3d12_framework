#ifndef DEPTH_STENCIL_CONFIG_H
#define DEPTH_STENCIL_CONFIG_H

#include <windef.h>
#include "CompareFuncs.h"
#include "GraphicsDataFormat.h"

/// <summary>
/// Enum of the various stencil operations
/// </summary>
/// <remarks>
/// Values must match D3D12_STENCIL_OP
/// </remarks>
enum StencilOp
{
  SOP_KEEP = 1,
  SOP_ZERO,
  SOP_REPLACE,
  SOP_INCREMENT_CLAMP,
  SOP_DECREMENT_CLAMP,
  SOP_INVERT,
  SOP_INCREMENT_ROLLOVER,
  SOP_DECREMENT_ROLLOVER
};

/// <summary>
/// Configuration for processing pixels
/// </summary>
struct StencilOpConfig
{
  /// <summary>
  /// Stencil operation to perform when stencil testing fails
  /// </summary>
  StencilOp stencil_fail;

  /// <summary>
  /// Stencil operation to perform when stencil testing passes, but depth testing fails
  /// </summary>
  StencilOp depth_fail;

  /// <summary>
  /// Stencil operation to perform when both stencil and depth testing pass
  /// </summary>
  StencilOp pass;

  /// <summary>
  /// Comparison function to use to compare stencil data against existing stencil data
  /// </summary>
  CompareFuncs comparison;
};

/// <summary>
/// Configuration for the depth stencil
/// </summary>
struct DepthStencilConfig
{
  /// <summary>
  /// true if depth testing is enabled.  false otherwise
  /// </summary>
  bool depth_enable;

  /// <summary>
  /// true if stencil testing is enabled.  false otherwise
  /// </summary>
  bool stencil_enable;

  /// <summary>
  /// Format of the depth stencil view.  Must be correctly set if either depth_enable or stencil_enable is set to true.
  /// </summary>
  GraphicsDataFormat dsv_format;

  /// <summary>
  /// true if writing to the depth portion of the depth stencil is allowed.  false otherwise.
  /// </summary>
  bool depth_write_enabled;

  /// <summary>
  /// Comparison function to use to compare depth data against existing depth data
  /// </summary>
  CompareFuncs depth_comparison;

  /// <summary>
  /// Bitmask for identifying which portion of the depth stencil should be used for reading stencil data
  /// </summary>
  UINT8 stencil_read_mask;

  /// <summary>
  /// Bitmask for identifying which portion of the depth stencil should be used for writing stencil data
  /// </summary>
  UINT8 stencil_write_mask;

  /// <summary>
  /// Configuration for processing pixels with a surface normal towards the camera
  /// </summary>
  StencilOpConfig stencil_front_face;

  /// <summary>
  /// Configuration for processing pixels with a surface normal away from the camera
  /// </summary>
  StencilOpConfig stencil_back_face;
};

#endif /* DEPTH_STENCIL_CONFIG_H */
