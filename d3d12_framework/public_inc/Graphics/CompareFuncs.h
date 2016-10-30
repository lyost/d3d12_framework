#ifndef COMPARE_FUNCS_H
#define COMPARE_FUNCS_H

/// <summary>
/// Enum of the various comparision functions
/// </summary>
/// <remarks>
/// Values must match D3D12_COMPARISON_FUNC
/// </remarks>
enum CompareFuncs
{
  COMPARISON_FUNC_NEVER = 1,
  COMPARISON_FUNC_LESS,
  COMPARISON_FUNC_EQUAL,
  COMPARISON_FUNC_LESS_EQUAL,
  COMPARISON_FUNC_GREATER,
  COMPARISON_FUNC_NOT_EQUAL,
  COMPARISON_FUNC_GREATER_EQUAL,
  COMPARISON_FUNC_ALWAYS
};

#endif /* COMPARE_FUNCS_H */
