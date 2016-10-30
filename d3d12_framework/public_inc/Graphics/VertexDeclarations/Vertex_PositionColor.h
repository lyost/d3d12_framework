#ifndef VERTEX_POSITION_COLOR_H
#define VERTEX_POSITION_COLOR_H

#include <directxmath.h>

/// <summary>
/// For vertices that are comprised of just a position and rgba color
/// </summary>
struct Vertex_PositionColor
{
  DirectX::XMFLOAT3 pos;
  DirectX::XMFLOAT4 color;
};

#endif /* VERTEX_POSITION_COLOR_H */
