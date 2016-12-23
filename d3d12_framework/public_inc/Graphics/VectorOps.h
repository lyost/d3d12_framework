#ifndef VECTOR_OPS_H
#define VECTOR_OPS_H

/// <summary>
/// Component-wise vector math operations
/// </summary>
/// <remarks>
/// While all of these operations are available with XMVECTOR, there are times
/// it's convient not to have to convert a DirectX::XMFLOAT* into a XMVECTOR to get
/// access to them.
/// </remarks>

#include <windows.h>
#include <directxmath.h>

// XMFLOAT2 ops

DirectX::XMFLOAT2 operator+(const DirectX::XMFLOAT2& left,const DirectX::XMFLOAT2& right);
DirectX::XMFLOAT2 operator-(const DirectX::XMFLOAT2& left,const DirectX::XMFLOAT2& right);
DirectX::XMFLOAT2 operator*(const DirectX::XMFLOAT2& left,const DirectX::XMFLOAT2& right);
DirectX::XMFLOAT2 operator*(const DirectX::XMFLOAT2& left,float right);
DirectX::XMFLOAT2 operator/(const DirectX::XMFLOAT2& left,const DirectX::XMFLOAT2& right);
DirectX::XMFLOAT2 operator-(const DirectX::XMFLOAT2& left);

DirectX::XMFLOAT2& operator+=(DirectX::XMFLOAT2& left,const DirectX::XMFLOAT2& right);
DirectX::XMFLOAT2& operator-=(DirectX::XMFLOAT2& left,const DirectX::XMFLOAT2& right);
DirectX::XMFLOAT2& operator*=(DirectX::XMFLOAT2& left,const DirectX::XMFLOAT2& right);
DirectX::XMFLOAT2& operator*=(DirectX::XMFLOAT2& left,float right);
DirectX::XMFLOAT2& operator/=(DirectX::XMFLOAT2& left,const DirectX::XMFLOAT2& right);

// XMFLOAT3 ops

DirectX::XMFLOAT3 operator+(const DirectX::XMFLOAT3& left,const DirectX::XMFLOAT3& right);
DirectX::XMFLOAT3 operator-(const DirectX::XMFLOAT3& left,const DirectX::XMFLOAT3& right);
DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3& left,const DirectX::XMFLOAT3& right);
DirectX::XMFLOAT3 operator*(const DirectX::XMFLOAT3& left,float right);
DirectX::XMFLOAT3 operator/(const DirectX::XMFLOAT3& left,const DirectX::XMFLOAT3& right);
DirectX::XMFLOAT3 operator-(const DirectX::XMFLOAT3& left);

DirectX::XMFLOAT3& operator+=(DirectX::XMFLOAT3& left,const DirectX::XMFLOAT3& right);
DirectX::XMFLOAT3& operator-=(DirectX::XMFLOAT3& left,const DirectX::XMFLOAT3& right);
DirectX::XMFLOAT3& operator*=(DirectX::XMFLOAT3& left,const DirectX::XMFLOAT3& right);
DirectX::XMFLOAT3& operator*=(DirectX::XMFLOAT3& left,float right);
DirectX::XMFLOAT3& operator/=(DirectX::XMFLOAT3& left,const DirectX::XMFLOAT3& right);

// XMFLOAT4 ops

DirectX::XMFLOAT4 operator+(const DirectX::XMFLOAT4& left,const DirectX::XMFLOAT4& right);
DirectX::XMFLOAT4 operator-(const DirectX::XMFLOAT4& left,const DirectX::XMFLOAT4& right);
DirectX::XMFLOAT4 operator*(const DirectX::XMFLOAT4& left,const DirectX::XMFLOAT4& right);
DirectX::XMFLOAT4 operator*(const DirectX::XMFLOAT4& left,float right);
DirectX::XMFLOAT4 operator/(const DirectX::XMFLOAT4& left,const DirectX::XMFLOAT4& right);
DirectX::XMFLOAT4 operator-(const DirectX::XMFLOAT4& left);

DirectX::XMFLOAT4& operator+=(DirectX::XMFLOAT4& left,const DirectX::XMFLOAT4& right);
DirectX::XMFLOAT4& operator-=(DirectX::XMFLOAT4& left,const DirectX::XMFLOAT4& right);
DirectX::XMFLOAT4& operator*=(DirectX::XMFLOAT4& left,const DirectX::XMFLOAT4& right);
DirectX::XMFLOAT4& operator*=(DirectX::XMFLOAT4& left,float right);
DirectX::XMFLOAT4& operator/=(DirectX::XMFLOAT4& left,const DirectX::XMFLOAT4& right);

#endif /* VECTOR_OPS_H */
