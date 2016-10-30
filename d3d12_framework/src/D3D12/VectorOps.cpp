#include "Graphics/VectorOps.h"
using namespace DirectX;

XMFLOAT2 operator+(const XMFLOAT2& left,const XMFLOAT2& right)
{
  return XMFLOAT2(
    left.x + right.x,
    left.y + right.y);
}

XMFLOAT2 operator-(const XMFLOAT2& left,const XMFLOAT2& right)
{
  return XMFLOAT2(
    left.x - right.x,
    left.y - right.y);
}

XMFLOAT2 operator*(const XMFLOAT2& left,const XMFLOAT2& right)
{
  return XMFLOAT2(
    left.x * right.x,
    left.y * right.y);
}

XMFLOAT2 operator*(const XMFLOAT2& left,float right)
{
  return XMFLOAT2(
    left.x * right,
    left.y * right);
}

XMFLOAT2 operator/(const XMFLOAT2& left,const XMFLOAT2& right)
{
  return XMFLOAT2(
    left.x / right.x,
    left.y / right.y);
}

XMFLOAT2 operator-(const XMFLOAT2& left)
{
  return XMFLOAT2(
    -left.x,
    -left.y);
}

XMFLOAT2& operator+=(XMFLOAT2& left,const XMFLOAT2& right)
{
  left.x += right.x;
  left.y += right.y;
  
  return left;
}

XMFLOAT2& operator-=(XMFLOAT2& left,const XMFLOAT2& right)
{
  left.x -= right.x;
  left.y -= right.y;
  
  return left;
}

XMFLOAT2& operator*=(XMFLOAT2& left,const XMFLOAT2& right)
{
  left.x *= right.x;
  left.y *= right.y;
  
  return left;
}

XMFLOAT2& operator*=(XMFLOAT2& left,float right)
{
  left.x *= right;
  left.y *= right;
  
  return left;
}

XMFLOAT2& operator/=(XMFLOAT2& left,const XMFLOAT2& right)
{
  left.x /= right.x;
  left.y /= right.y;
  
  return left;
}

XMFLOAT3 operator+(const XMFLOAT3& left,const XMFLOAT3& right)
{
  return XMFLOAT3(
    left.x + right.x,
    left.y + right.y,
    left.z + right.z);
}

XMFLOAT3 operator-(const XMFLOAT3& left,const XMFLOAT3& right)
{
  return XMFLOAT3(
    left.x - right.x,
    left.y - right.y,
    left.z - right.z);
}

XMFLOAT3 operator*(const XMFLOAT3& left,const XMFLOAT3& right)
{
  return XMFLOAT3(
    left.x * right.x,
    left.y * right.y,
    left.z * right.z);
}

XMFLOAT3 operator*(const XMFLOAT3& left,float right)
{
  return XMFLOAT3(
    left.x * right,
    left.y * right,
    left.z * right);
}

XMFLOAT3 operator/(const XMFLOAT3& left,const XMFLOAT3& right)
{
  return XMFLOAT3(
    left.x / right.x,
    left.y / right.y,
    left.z / right.z);
}

XMFLOAT3 operator-(const XMFLOAT3& left)
{
  return XMFLOAT3(
    -left.x,
    -left.y,
    -left.z);
}

XMFLOAT3& operator+=(XMFLOAT3& left,const XMFLOAT3& right)
{
  left.x += right.x;
  left.y += right.y;
  left.z += right.z;
  
  return left;
}

XMFLOAT3& operator-=(XMFLOAT3& left,const XMFLOAT3& right)
{
  left.x -= right.x;
  left.y -= right.y;
  left.z -= right.z;
  
  return left;
}

XMFLOAT3& operator*=(XMFLOAT3& left,const XMFLOAT3& right)
{
  left.x *= right.x;
  left.y *= right.y;
  left.z *= right.z;
  
  return left;
}

XMFLOAT3& operator*=(XMFLOAT3& left,float right)
{
  left.x *= right;
  left.y *= right;
  left.z *= right;
  
  return left;
}

XMFLOAT3& operator/=(XMFLOAT3& left,const XMFLOAT3& right)
{
  left.x /= right.x;
  left.y /= right.y;
  left.z /= right.z;
  
  return left;
}

XMFLOAT4 operator+(const XMFLOAT4& left,const XMFLOAT4& right)
{
  return XMFLOAT4(
    left.x + right.x,
    left.y + right.y,
    left.z + right.z,
    left.w + right.w);
}

XMFLOAT4 operator-(const XMFLOAT4& left,const XMFLOAT4& right)
{
  return XMFLOAT4(
    left.x - right.x,
    left.y - right.y,
    left.z - right.z,
    left.w - right.w);
}

XMFLOAT4 operator*(const XMFLOAT4& left,const XMFLOAT4& right)
{
  return XMFLOAT4(
    left.x * right.x,
    left.y * right.y,
    left.z * right.z,
    left.w * right.w);
}

XMFLOAT4 operator*(const XMFLOAT4& left,float right)
{
  return XMFLOAT4(
    left.x * right,
    left.y * right,
    left.z * right,
    left.w * right);
}

XMFLOAT4 operator/(const XMFLOAT4& left,const XMFLOAT4& right)
{
  return XMFLOAT4(
    left.x / right.x,
    left.y / right.y,
    left.z / right.z,
    left.w / right.w);
}

XMFLOAT4 operator-(const XMFLOAT4& left)
{
  return XMFLOAT4(
    -left.x,
    -left.y,
    -left.z,
    -left.w);
}

XMFLOAT4& operator+=(XMFLOAT4& left,const XMFLOAT4& right)
{
  left.x += right.x;
  left.y += right.y;
  left.z += right.z;
  left.w += right.w;
  
  return left;
}

XMFLOAT4& operator-=(XMFLOAT4& left,const XMFLOAT4& right)
{
  left.x -= right.x;
  left.y -= right.y;
  left.z -= right.z;
  left.w -= right.w;
  
  return left;
}

XMFLOAT4& operator*=(XMFLOAT4& left,const XMFLOAT4& right)
{
  left.x *= right.x;
  left.y *= right.y;
  left.z *= right.z;
  left.w *= right.w;
  
  return left;
}

XMFLOAT4& operator*=(XMFLOAT4& left,float right)
{
  left.x *= right;
  left.y *= right;
  left.z *= right;
  left.w *= right;
  
  return left;
}

XMFLOAT4& operator/=(XMFLOAT4& left,const XMFLOAT4& right)
{
  left.x /= right.x;
  left.y /= right.y;
  left.z /= right.z;
  left.w /= right.w;
  
  return left;
}
