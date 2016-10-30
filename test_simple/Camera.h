#ifndef CAMERA_H
#define CAMERA_H

#include <windows.h>
#include <directxmath.h>

class Camera
{
  public:
    /// <summary>
    /// Creates a camera based on the specified data
    /// </summary>
    /// <param name="aspect_ratio">
    /// Aspect ratio for the camera
    /// </param>
    /// <param name="pos">
    /// Position of the camera
    /// </param>
    /// <param name="dir">
    /// Normalized vector representing the direction the camera is pointing
    /// </param>
    /// <param name="up">
    /// Normalized vector representing which direction is up for the camera
    /// </param>
    Camera(float aspect_ratio,DirectX::XMFLOAT4 pos,DirectX::XMFLOAT4 dir,
      DirectX::XMFLOAT4 up);
    
    ~Camera();
    
    /// <summary>
    /// Changes the camera's aspect ratio to the specified value
    /// </summary>
    /// <param name="aspect_ratio">
    /// Aspect ratio for the camera
    /// </param>
    void SetAspecRatio(float aspect_ratio);
    
    /// <summary>
    /// Retrieves the view matrix
    /// <remarks>
    /// The view matrix is done as a XMMATRIX instead of a XMFLOAT4X4 since the
    /// matrix needs to be transposed before being sent to a shader
    /// </remarks>
    /// </summary>
    /// <param name="view">
    /// where to put the view matrix
    /// </param>
    void GetView(DirectX::XMMATRIX& view);
    
    /// <summary>
    /// Retrieves the projection matrix
    /// <remarks>
    /// The projection matrix is done as a XMMATRIX instead of a XMFLOAT4X4
    /// since the matrix needs to be transposed before being sent to a shader
    /// </remarks>
    /// </summary>
    /// <param name="proj">
    /// where to put the proj matrix
    /// </param>
    void GetProj(DirectX::XMMATRIX& proj);
    
  private:
    // disabled
    Camera();
    Camera(const Camera& cpy);
    Camera& operator=(const Camera& cpy);
    
    /// <summary>
    /// position of the camera in world space
    /// </summary>
    DirectX::XMFLOAT4 m_pos;
    
    /// <summary>
    /// normalized direction the camrea is facing
    /// </summary>
    DirectX::XMFLOAT4 m_dir;
    
    /// <summary>
    /// normalized up vector for the camera
    /// </summary>
    DirectX::XMFLOAT4 m_up;
    
    /// <summary>
    /// view matrix
    /// </summary>
    DirectX::XMFLOAT4X4 m_view;
    
    /// <summary>
    /// projection matrix
    /// </summary>
    DirectX::XMFLOAT4X4 m_proj;
};

#endif /* CAMERA_H */