#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include "Game.h"
#include "Graphics/RootSignature.h"
#include "Graphics/Shader.h"
#include "Graphics/InputLayout.h"
#include "Graphics/Pipeline.h"
#include "Graphics/CommandListBundle.h"
#include "Graphics/Buffers/VertexBuffer_PositionColor.h"
#include "Graphics/BufferResourceHeap.h"
#include "Graphics/ShaderResourceDescHeap.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/HeapArray.h"

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
    VertexBuffer_PositionColor* m_verts;

    /// <summary>
    /// vertex buffer array for supplying the vertex buffer to the rendering process
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
    /// Constant buffer 
    /// </summary>
    ConstantBuffer* m_constant_buffer;
    
    /// <summary>
    /// viewports to use
    /// </summary>
    Viewports m_viewports;

    /// <summary>
    /// corresponding scissor rect for m_viewports's first viewport
    /// </summary>
    RECT m_scissor_rect;
};

#endif /* GAMEMAIN_H */
