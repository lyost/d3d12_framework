#ifndef VERTEX_POSITION_TEXTURE_H
#define VERTEX_POSITION_TEXTURE_H

#include <directxmath.h>

/// <summary>
/// For vertices that are comprised of just a position and u coordinates
/// </summary>
struct Vertex_PositionTextureU
{
  DirectX::XMFLOAT3 pos;
  float             u;
};

/// <summary>
/// For vertices that are comprised of just a position and uv coordinates
/// </summary>
struct Vertex_PositionTextureUV
{
  DirectX::XMFLOAT3 pos;
  DirectX::XMFLOAT2 uv;
};

/// <summary>
/// For vertices that are comprised of just a position and uvw coordinates
/// </summary>
struct Vertex_PositionTextureUVW
{
  DirectX::XMFLOAT3 pos;
  DirectX::XMFLOAT3 uvw;
};

#endif /* VERTEX_POSITION_TEXTURE_H */
