#ifndef SHADER_VISIBILITY_H
#define SHADER_VISIBILITY_H

/// <summary>
/// Enum of the various shader visibilities for parameters and samplers of root signatures
/// </summary>
/// <remarks>
/// Values must match the values of D3D12_SHADER_VISIBILITY
/// </remarks>
enum ShaderVisibility
{
  SHADER_VISIBILITY_ALL = 0,
  SHADER_VISIBILITY_VERTEX,
  SHADER_VISIBILITY_HULL,
  SHADER_VISIBILITY_DOMAIN,
  SHADER_VISIBILITY_GEOMETRY,
  SHADER_VISIBILITY_PIXEL
};

#endif /* SHADER_VISIBILITY_H */
