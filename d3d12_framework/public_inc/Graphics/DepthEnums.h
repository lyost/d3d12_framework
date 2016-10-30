#ifndef DEPTH_ENUMS_H
#define DEPTH_ENUMS_H

/// <summary>
/// Enum of the various depth comparision functions
/// </summary>
/// <remarks>
/// Values must match D3D12_COMPARISON_FUNC
/// </remarks>
enum DepthFuncs
{
  DEPTH_FUNC_NEVER = 1,
  DEPTH_FUNC_LESS,
  DEPTH_FUNC_EQUAL,
  DEPTH_FUNC_LESS_EQUAL,
  DEPTH_FUNC_GREATER,
  DEPTH_FUNC_NOT_EQUAL,
  DEPTH_FUNC_GREATER_EQUAL,
  DEPTH_FUNC_ALWAYS
};

#endif /* DEPTH_ENUMS_H */
