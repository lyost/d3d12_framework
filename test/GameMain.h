#ifndef GAMEMAIN_H
#define GAMEMAIN_H

// d3d11_framework header files
#include "Game.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Shader.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Pipeline.h"
#include "Graphics/Buffers/VertexBuffer_PositionTexture.h"
#include "Graphics/Buffers/VertexBuffer_Custom.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Buffers/VertexBufferArray.h"
#include "Graphics/Viewports.h"
/*
#include "Graphics/Texture/ShaderResourceView.h"
#include "Graphics/Texture/TextureSampler.h"
#include "Graphics/Texture/RenderTargetView.h"
#include "Graphics/Texture/DepthStencilView.h"
*/

// local project header file(s)
#include "Camera.h"

class GameMain : public Game
{
  public:
    GameMain(WCHAR* title);
    ~GameMain();
    
  protected:
    /// <summary>
    /// Loads the content for the game
    /// </summary>
    /// <param name="content">
    /// content manager to use for loading resources
    /// </param>
    void LoadContent();
    
    /// <summary>
    /// Unloads the content for the game before the dealloction of the instance
    /// </summary>
    /// <param name="content">
    /// content manager to use for unloading resources
    /// </param>
    void UnloadContent();
    
    /// <summary>
    /// Updates the game state
    /// </summary>
    /// <param name="ms">
    /// number of milliseconds since the update
    /// </param>
    void Update(UINT ms);
    
    /// <summary>
    /// Draws the current frame
    /// </summary>
    /// <param name="ms">
    /// number of milliseconds since the last frame
    /// </param>
    void Draw(UINT ms);
    
    /// <summary>
    /// Handler for when the window is resized
    /// </summary>
    /// <param name="width">
    /// width of the new client area, in pixels 
    /// </param>
    /// <param name="height">
    /// height of the new client area, in pixels
    /// </param>
    void OnResize(UINT width,UINT height);
    
  private:
    // disabled
    GameMain(const GameMain& cpy);
    GameMain& operator=(const GameMain& cpy);
    
    /// <summary>
    /// setups the data members for displaying the cube
    /// </summary>
    void LoadCube();
    
    /// <summary>
    /// setups the data members for the render target view test
    /// </summary>
    void Load_RTV_Test();
    
    /// <summary>
    /// root signatures for both cube and rtv test
    /// </summary>
    RootSignature* m_root_sig;
    
    /// <summary>
    /// test vertex shaders (0 = cube, 1 = rtv test)
    /// </summary>
    Shader* m_vertex_shader[2];
    
    /// <summary>
    /// test pixel shader (0 = cube, 1 = rtv test)
    /// </summary>
    Shader* m_pixel_shader[2];

    /// <summary>
    /// input layouts for the vertex shaders (0 = cube, 1 = rtv test)
    /// </summary>
    InputLayout* m_input_layout[2];

    /// <summary>
    /// graphics pipelines (0 = cube, 1 = rtv test)
    /// </summary>
    Pipeline* m_pipeline[2];

    /// <summary>
    /// vertex buffer for the test cases (0 = cube, 1 = rtv test)
    /// </summary>
    VertexBuffer_PositionTexture* m_verts[2];

    /// <summary>
    /// index buffer for the test cases (0 = cube, 1 = rtv test)
    /// </summary>
    IndexBuffer16* m_indices[2];

    /// <summary>
    /// instance buffer for the test cube
    /// </summary>
    VertexBuffer_Custom* m_instance;

    /// <summary>
    /// vertex buffer array for supplying the vertex and instance buffers to the rendering process
    /// </summary>
    VertexBufferArray* m_vert_array;

#if 0

    /// <summary>
    /// textures to apply to the cube (0 = file, 1 = test prog created/updated,
    /// 2 = rtv test, 3 = depth stencil texture that is part of rtv test and
    /// does not need a shader resource view)
    /// </summary>
    Texture* m_texture[4];
    
    /// <summary>
    /// shader resource views of the textures to apply to the cube (parallel
    /// array with m_texture, aside from the depth texture)
    /// </summary>
    ShaderResourceView* m_texture_view[3];
    
    /// <summary>
    /// texture sampler to use
    /// </summary>
    TextureSampler* m_sampler;
    
    /// <summary>
    /// render target view of m_texture[2] for the rtv test
    /// </summary>
    RenderTargetView* m_rtv;
    
    /// <summary>
    /// depth stencil view of m_texture[3] that is needed in order to specify
    /// the rtv for m_texture[2]
    /// </summary>
    DepthStencilView* m_dsv;
#endif /* 0 */

    /// <summary>
    /// cameras for the 4 test viewports
    /// </summary>
    Camera* m_cameras[4];

    /// <summary>
    /// cameras for the rtv test
    /// </summary>
    Camera* m_camera_rtv;
    
    /// <summary>
    /// viewports to test the viewport functionality
    /// </summary>
    Viewports m_viewports;
};

#endif /* GAMEMAIN_H */
