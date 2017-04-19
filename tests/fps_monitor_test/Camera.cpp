#include "Camera.h"
#include "Graphics/VectorOps.h"
using namespace DirectX;

Camera::Camera(float aspect_ratio, float near_z, float far_z,XMFLOAT4 pos,XMFLOAT4 dir,XMFLOAT4 up)
{
  SetView(pos, dir, up);
  SetProjection(aspect_ratio, near_z, far_z);
}

Camera::~Camera()
{
}

void Camera::SetView(XMFLOAT4 pos, XMFLOAT4 dir, XMFLOAT4 up)
{
  XMVECTOR pos_tmp = XMLoadFloat4(&pos);
  XMFLOAT4 at = pos + dir;
  XMVECTOR at_tmp = XMLoadFloat4(&at);
  XMVECTOR up_tmp = XMLoadFloat4(&up);

  XMStoreFloat4x4(&m_view, XMMatrixLookAtLH(pos_tmp, at_tmp, up_tmp));
}

void Camera::SetProjection(float aspect_ratio, float near_z, float far_z)
{
  XMStoreFloat4x4(&m_proj, XMMatrixPerspectiveFovLH(XM_PIDIV4, aspect_ratio, near_z, far_z));
}

void Camera::GetView(XMMATRIX& view) const
{
  view = XMLoadFloat4x4(&m_view);
}

void Camera::GetProjection(XMMATRIX& proj) const
{
  proj = XMLoadFloat4x4(&m_proj);
}
