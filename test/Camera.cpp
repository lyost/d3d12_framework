#include "Camera.h"
#include "Graphics/VectorOps.h"
using namespace DirectX;

Camera::Camera(float aspect_ratio,XMFLOAT4 pos,XMFLOAT4 dir,XMFLOAT4 up)
:m_pos(pos),
 m_dir(dir),
 m_up(up)
{
  XMVECTOR pos_tmp = XMLoadFloat4(&m_pos);
  XMFLOAT4 at      = pos + dir;
  XMVECTOR at_tmp  = XMLoadFloat4(&at);
  XMVECTOR up_tmp  = XMLoadFloat4(&up);
  
  XMStoreFloat4x4(&m_view,XMMatrixLookAtLH(pos_tmp,at_tmp,up_tmp));

  XMStoreFloat4x4(&m_proj,
    XMMatrixPerspectiveFovLH(XM_PIDIV4,aspect_ratio,0.01f,100.0f));
}

Camera::~Camera()
{
}

void Camera::SetAspecRatio(float aspect_ratio)
{
  XMStoreFloat4x4(&m_proj,
    XMMatrixPerspectiveFovLH(XM_PIDIV4,aspect_ratio,0.01f,100.0f));
}

void Camera::GetView(XMMATRIX& view)
{
  view = XMLoadFloat4x4(&m_view);
}

void Camera::GetProj(XMMATRIX& proj)
{
  proj = XMLoadFloat4x4(&m_proj);
}
