#ifndef TOPOLOGY_H
#define TOPOLOGY_H

/// <summary>
/// Enum of the various topologies for geometry and hull shader stages
/// </summary>
/// <remarks>
/// Values must match D3D12_PRIMITIVE_TOPOLOGY_TYPE
/// </remarks>
enum Topology
{
  TOPOLOGY_UNDEFINED = 0,
  TOPOLOGY_POINT     = 1,
  TOPOLOGY_LINE      = 2,
  TOPOLOGY_TRIANGLE  = 3,
  TOPOLOGY_PATCH     = 4
};

/// <summary>
/// Enum of the various topologies for the input assembler stage
/// </summary>
/// <remarks>
/// Values must match D3D_PRIMITIVE_TOPOLOGY
/// </remarks>
enum IATopology
{
  IA_TOPOLOGY_UNDEFINED             = 0,
  IA_TOPOLOGY_POINT_LIST            = 1,
  IA_TOPOLOGY_LINE_LIST             = 2,
  IA_TOPOLOGY_LINE_STRIP            = 3,
  IA_TOPOLOGY_TRIANGLE_LIST         = 4,
  IA_TOPOLOGY_TRIANGLE_STRIP        = 5,
  IA_TOPOLOGY_4_CONTROL_POINT_PATCH = 36,
  // todo: fill in the rest of the types
};

#endif /* TOPOLOGY_H */
