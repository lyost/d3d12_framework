#ifndef VERTEX_POSITION_TEXTURE_H
#define VERTEX_POSITION_TEXTURE_H

#include <directxmath.h>

/// <summary>
/// For vertices that are comprised of just a position and uv coordinates
/// </summary>
struct Vertex_PositionTexture
{
  DirectX::XMFLOAT3 pos;
  DirectX::XMFLOAT2 uv;
};

#endif /* VERTEX_POSITION_TEXTURE_H */
