#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include <vector>
#include "Game.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Shader.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Pipeline.h"
#include "Graphics/CommandListBundle.h"
#include "Graphics/Buffers/VertexBuffer_PositionTexture.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Camera.h"
#include "Graphics/ShaderResourceDescHeap.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/HeapArray.h"
#include "Graphics/Textures/Texture1D.h"
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Textures/Texture3D.h"
#include "Graphics/Textures/Texture1DArray.h"
#include "Graphics/Textures/Texture2DArray.h"
#include "Graphics/Textures/TextureCube.h"
#include "Graphics/Textures/TextureCubeArray.h"
#include "Graphics/Textures/TextureUploadBuffer.h"
#include "Graphics/Textures/DepthStencil.h"
#include "Graphics/Textures/RenderTargetMSAA.h"
#include "Graphics/Textures/DepthStencilMSAA.h"

class GameMain : public Game
{
  public:
    GameMain(WCHAR* title);
    ~GameMain();
    
  protected:
    /// <summary>
    /// Loads the content for the game
    /// </summary>
    void LoadContent();
    
    /// <summary>
    /// Unloads the content for the game before the dealloction of the instance
    /// </summary>
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

    enum
    {
      TEXTURE_MODE_1D = 0,
      TEXTURE_MODE_2D,
      TEXTURE_MODE_3D,
      TEXTURE_MODE_1D_ARRAY,
      TEXTURE_MODE_2D_ARRAY,
      TEXTURE_MODE_CUBE,
      TEXTURE_MODE_CUBE_ARRAY,
      TEXTURE_MODE_MAX
    };

    enum
    {
      TEXTURE_WIDTH     = 64,
      TEXTURE_HEIGHT    = 64,
      TEXTURE_DEPTH     = 8,
      TEXTURE_FORMAT    = R8B8G8A8_UNORM,
      NUM_MIPMAPS       = 2,
      ARRAY_SIZE        = 2,
      TEXTURES_PER_CUBE = 6
    };

    /// <summary>
    /// Creates a test 1D texture
    /// </summary>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture1D(UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates a test 2D texture
    /// </summary>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture2D(UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates a test 3D texture
    /// </summary>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture3D(UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates a test 1D texture for the 2D texture array
    /// </summary>
    /// <param name="index">
    /// index into the texture array for which texture to create
    /// </param>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture1DArray(UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates a test 2D texture for the 2D texture array
    /// </summary>
    /// <param name="index">
    /// index into the texture array for which texture to create
    /// </param>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTexture2DArray(UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates textures for the texture cube
    /// </summary>
    /// <param name="indes">
    /// index of which side to create the texture for
    /// </param>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTextureCube(UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Creates textures for the texture cube array
    /// </summary>
    /// <param name="cube">
    /// index of which cube to create the textures for
    /// </param>
    /// <param name="index">
    /// index of which side to create the texture for
    /// </param>
    /// <param name="mipmap">
    /// index of which mipmap level to create the texture for
    /// </param>
    /// <param name="bytes">
    /// bytes of the image
    /// </param>
    static void CreateTextureCubeArray(UINT16 cube, UINT16 index, UINT16 mipmap, std::vector<UINT8>& bytes);

    /// <summary>
    /// Updates m_camera based on m_camera_angle
    /// </summary>
    void UpdateCamera();

    /// <summary>
    /// Helper function for creating the depth stencil on load and on resize
    /// </summary>
    void CreateDepthStencil();
    
    /// <summary>
    /// root signatures for the test case
    /// </summary>
    RootSignature* m_root_sig;
    
    /// <summary>
    /// test vertex shader
    /// </summary>
    Shader* m_vertex_shader;
    
    /// <summary>
    /// test pixel shader
    /// </summary>
    Shader* m_pixel_shader;

    /// <summary>
    /// input layouts for the vertex shader
    /// </summary>
    InputLayout* m_input_layout;

    /// <summary>
    /// graphics pipeline
    /// </summary>
    Pipeline* m_pipeline;

    /// <summary>
    /// command list to draw with
    /// </summary>
    CommandList* m_command_list;

    /// <summary>
    /// vertex buffer for the test case
    /// </summary>
    VertexBuffer_PositionTexture* m_verts;

    /// <summary>
    /// index buffer for the test case
    /// </summary>
    IndexBuffer16* m_indices;

    /// <summary>
    /// vertex buffer array for supplying the vertex buffer to the rendering process
    /// </summary>
    VertexBufferArray* m_vert_array;

    /// <summary>
    /// instance buffer for the test cube
    /// </summary>
    VertexBuffer_Custom* m_instance;
    
    /// <summary>
    /// viewports to use
    /// </summary>
    Viewports m_viewports;

    /// <summary>
    /// corresponding scissor rect for m_viewports's first viewport
    /// </summary>
    RECT m_scissor_rect;

    /// <summary>
    /// camera for the test viewport
    /// </summary>
    Camera* m_camera;

    /// <summary>
    /// angle (in radians) of the camera orbiting the world space's origin
    /// </summary>
    float m_camera_angle;

    /// <summary>
    /// angle (in radians) of the camera pitch orbiting the world space's origin
    /// </summary>
    float m_camera_pitch;

    /// <summary>
    /// Descriptor Heap for allocating the buffers from
    /// </summary>
    ShaderResourceDescHeap* m_shader_buffer_heap;

    /// <summary>
    /// array of descriptor heaps
    /// </summary>
    HeapArray* m_heap_array;

    /// <summary>
    /// Constant buffer 
    /// </summary>
    ConstantBuffer* m_constant_buffer_vs;

    /// <summary>
    /// Constant buffer 
    /// </summary>
    ConstantBuffer* m_constant_buffer_ps;

    /// <summary>
    /// texture
    /// </summary>
    Texture1D* m_texture1d;

    /// <summary>
    /// texture
    /// </summary>
    Texture2D* m_texture2d;

    /// <summary>
    /// texture
    /// </summary>
    Texture3D* m_texture3d;

    /// <summary>
    /// texture
    /// </summary>
    Texture1DArray* m_texture1d_array;

    /// <summary>
    /// texture
    /// </summary>
    Texture2DArray* m_texture2d_array;

    /// <summary>
    /// texture
    /// </summary>
    TextureCube* m_texture_cube;

    /// <summary>
    /// texture
    /// </summary>
    TextureCubeArray* m_texture_cube_array;

    /// <summary>
    /// buffer for uploading the texture's data
    /// </summary>
    std::vector<TextureUploadBuffer*> m_upload_texture;

    /// <summary>
    /// depth stencil
    /// </summary>
    DepthStencil* m_depth_stencil;

    /// <summary>
    /// MSAA render target
    /// </summary>
    RenderTargetMSAA* m_render_target_msaa;

    /// <summary>
    /// MSAA depth stencil
    /// </summary>
    DepthStencilMSAA* m_depth_stencil_msaa;

    /// <summary>
    /// current texturing mode
    /// </summary>
    UINT m_current_mode;
};

#endif /* GAMEMAIN_H */
