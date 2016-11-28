#ifndef GAMEMAIN_H
#define GAMEMAIN_H

// d3d11_framework header files
#include "Game.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Shader.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Pipeline.h"
#include "Graphics/CommandListBundle.h"
#include "Graphics/Buffers/VertexBuffer_PositionTexture.h"
#include "Graphics/Buffers/VertexBuffer_Custom.h"
#include "Graphics/Buffers/IndexBuffer16.h"
#include "Graphics/Buffers/VertexBufferArray.h"
#include "Graphics/Viewports.h"
#include "Graphics/BufferResourceHeap.h"
#include "Graphics/ShaderResourceDescHeap.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/HeapArray.h"

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
    /// root signatures for both cube and rtv test
    /// </summary>
    RootSignature* m_root_sig;
    
    /// <summary>
    /// test vertex shaders
    /// </summary>
    Shader* m_vertex_shader;
    
    /// <summary>
    /// test pixel shader
    /// </summary>
    Shader* m_pixel_shader;

    /// <summary>
    /// input layouts for the vertex shaders
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
    /// vertex buffer for the test cases
    /// </summary>
    VertexBuffer_PositionTexture* m_verts;

    /// <summary>
    /// index buffer for the test cases
    /// </summary>
    IndexBuffer16* m_indices;

    /// <summary>
    /// vertex buffer array for supplying the vertex and instance buffers to the rendering process
    /// </summary>
    VertexBufferArray* m_vert_array;

    /// <summary>
    /// Resource heap for allocating the buffers from
    /// </summary>
    BufferResourceHeap* m_resource_heap;

    /// <summary>
    /// Descriptor Heap for allocating the buffers from
    /// </summary>
    ShaderResourceDescHeap* m_shader_buffer_heap;

    /// <summary>
    /// array of descriptor heaps
    /// </summary>
    HeapArray* m_heap_array;

    /// <summary>
    /// constant buffer for passing the wvp matrix to the shaders
    /// </summary>
    ConstantBuffer* m_constant_buffer;

    /// <summary>
    /// camera for the test viewport
    /// </summary>
    Camera* m_camera;
    
    /// <summary>
    /// viewports to test the viewport functionality
    /// </summary>
    Viewports m_viewports;

    /// <summary>
    /// corresponding scissor rect for m_viewport
    /// </summary>
    RECT m_scissor_rect;
};

#endif /* GAMEMAIN_H */
