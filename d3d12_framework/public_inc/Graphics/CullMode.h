#ifndef CULL_MODE_H
#define CULL_MODE_H

/// <summary>
/// Enum of which triangles should be culled
/// </summary>
/// <remarks>
/// Values must match up to the values used by D3D12_CULL_MODE
/// </remarks>
enum CullMode
{
  CULL_NONE  = 1,
  CULL_FRONT = 2,
  CULL_BACK  = 3,
};

#endif /* CULL_MODE_H */
