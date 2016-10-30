#include "GameMain.h"
#include <directxmath.h>
#include "Graphics/RootSignatureConfig.h"
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RenderTargetViewFormats.h"
#include "Graphics/VertexDeclarations/Vertex_PositionTexture.h"
using namespace DirectX;

GameMain::GameMain(WCHAR* title)
:Game(title)
{
}

GameMain::~GameMain()
{
}

void GameMain::LoadContent()
{
  LoadCube();
}

void GameMain::UnloadContent()
{
  delete m_constant_buffer;
  delete m_vert_array;
  delete m_indices;
  delete m_verts;
  delete m_resource_heap;
  delete m_shader_buffer_heap;
  delete m_heap_array;
  delete m_vertex_shader;
  delete m_pixel_shader;
  delete m_input_layout;
  delete m_command_list;
  delete m_pipeline;
  delete m_root_sig;
}

void GameMain::Update(UINT ms)
{
  static bool resized = false;
  static bool fullscreen = false;
  
  Window& window = GetWindow();
  const KeyboardState& keyboard = window.GetKeyboardState();
  if (keyboard.IsKeyDown(VK_ESCAPE,false))
  {
    Exit();
  }
  else if (keyboard.IsKeyDown(VK_F1,false) && !resized)
  {
    window.Resize(1024,768);
    resized = true;
  }
#if 0
  else if (keyboard.IsKeyDown(VK_F2,false) && !fullscreen)
  {
    // enter full screen mode
    Fullscreen(true);
    fullscreen = true;
  }
  else if (keyboard.IsKeyDown(VK_F3,false) && fullscreen)
  {
    // return to window mode
    Fullscreen(false);
    fullscreen = false;
  }
#endif /* 0 */
  /*else if (keyboard.IsKeyDown('1',false))
  {
    m_pixel_shader[0]->UseTexture(m_texture_view[0],0);
  }
  else if (keyboard.IsKeyDown('2',false))
  {
    // update the test texture to all red
    ID3D11DeviceContext* context     = GetGraphics().GetImmediateContext();
    Texture2D*           tex         = (Texture2D*)m_texture[1];
    const D3D11_TEXTURE2D_DESC& desc = tex->GetTextureDesc();
    UINT                 index       = D3D11CalcSubresource(0,0,1);
    UINT                 width       = desc.Width;
    UINT                 total_size  = width * desc.Height;
    UINT32*              buffer      = new UINT32[total_size];
    for (UINT i = 0; i < total_size; ++i)
    {
      buffer[i] = 0xff0000ff;
    }
    // note: multiplication due to format being DXGI_FORMAT_R8G8B8A8_UNORM
    width *= sizeof(UINT32);
    m_texture[1]->Update(context,index,buffer,width,0,width * desc.Height);
    
    m_pixel_shader[0]->UseTexture(m_texture_view[1],0);
  }
  else if (keyboard.IsKeyDown('3',false))
  {
    // update the test texture to all blue
    ID3D11DeviceContext* context     = GetGraphics().GetImmediateContext();
    Texture2D*           tex         = (Texture2D*)m_texture[1];
    const D3D11_TEXTURE2D_DESC& desc = tex->GetTextureDesc();
    UINT                 index       = D3D11CalcSubresource(0,0,1);
    UINT                 width       = desc.Width;
    UINT                 total_size  = width * desc.Height;
    UINT32*              buffer      = new UINT32[total_size];
    for (UINT i = 0; i < total_size; ++i)
    {
      buffer[i] = 0xffff0000;
    }
    // note: multiplication due to format being DXGI_FORMAT_R8G8B8A8_UNORM
    width *= sizeof(UINT32);
    m_texture[1]->Update(context,index,buffer,width,0,width * desc.Height);
    
    m_pixel_shader[0]->UseTexture(m_texture_view[1],0);
  }
  else if (keyboard.IsKeyDown('4',false))
  {
    // save the defaults
    D3D11_Core& graphics = GetGraphics();
    ID3D11DeviceContext* context = graphics.GetImmediateContext();
    RenderTargetView& default_rtv = graphics.GetDefaultRenderTargetView();
    DepthStencilView& default_dsv = graphics.GetDefaultDepthStencilView();
    
    // prep work for the rtv test (create the output merger instance and
    // compute the wvp matrix, get the default viewport into a usable form)
    OutputMerger output_merger(graphics.GetDefaultBlendState(),
      graphics.GetDefaultDepthStencilState(),*m_dsv);
    output_merger.Set(0,m_rtv);
    XMMATRIX tmp;
    XMMATRIX wvp = XMMatrixIdentity();
    m_camera_rtv->GetView(tmp);
    wvp *= tmp;
    m_camera_rtv->GetProj(tmp);
    wvp *= tmp;
    wvp = XMMatrixTranspose(wvp);
    m_vertex_shader[1]->SetConstantBuffer(context,0,&wvp);
    
    // clear the render target and depth stencil
    m_rtv->Clear(context);
    m_dsv->Clear(context);
    
    // render the rtv shape to the texture for the rtv test
    m_viewports.MakeActive(context,4,1);
    m_verts[1]->MakeActive(context);
    m_indices[1]->MakeActive(context);
    m_vertex_shader[1]->MakeActive(context);
    m_pixel_shader[1]->MakeActive(context);
    output_merger.MakeActive(context);
    graphics.DrawIndexedPrimitives(context,
      D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,0,6);

    // restore the default render target (don't need to restore the viewports
    // since the active viewport is set during the normal rendering process)
    output_merger.Set(default_dsv);
    output_merger.Set(0,&default_rtv);
    output_merger.MakeActive(context);
    
    // have the cube pixel shader use the rtv texture
    m_pixel_shader[0]->UseTexture(m_texture_view[2],0);
  }*/
  else if (keyboard.IsKeyDown(VK_OEM_4,false))
  {
    window.ShowMousePointer(false);
  }
  else if (keyboard.IsKeyDown(VK_OEM_6,false))
  {
    window.ShowMousePointer(true);
  }
  else if (keyboard.IsKeyDown('9',false))
  {
    window.ConstrainMousePointer(true);
  }
  else if (keyboard.IsKeyDown('0',false))
  {
    bool foo = window.ConstrainMousePointer(false);
  }
}

void GameMain::Draw(UINT ms)
{
  GraphicsCore& graphics = GetGraphics();
  const RenderTarget& currentRenderTarget = graphics.GetBackBuffer().GetCurrentRenderTarget();
  m_command_list->Reset(m_pipeline);
  m_command_list->SetRootSignature(*m_root_sig);
  m_command_list->RSSetViewport(graphics.GetDefaultViewport());
  m_command_list->RSSetScissorRect(m_scissor_rect);
  
  // todo:
  //ID3D12DescriptorHeap* ppHeaps[] = { m_cbvHeap.Get() };
  //m_commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
  //m_commandList->SetGraphicsRootDescriptorTable(0, m_cbvHeap->GetGPUDescriptorHandleForHeapStart());

  float clear_color[4] = { .3f, .3f, .3f, 1 };
  m_command_list->PrepRenderTarget(currentRenderTarget);
  m_command_list->OMSetRenderTarget(currentRenderTarget);
  m_command_list->ClearRenderTarget(currentRenderTarget, clear_color);

  m_command_list->IASetTopology(IA_TOPOLOGY_TRIANGLE_LIST);
  m_command_list->IASetIndexBuffer(*m_indices);
  m_command_list->IASetVertexBuffers(*m_vert_array);
  
  // todo: query index and vertex arrays for counts instead of hardcoding
  m_command_list->DrawIndexedInstanced(36, 2, 0);

  m_command_list->RenderTargetToPresent(currentRenderTarget);
  m_command_list->Close();
  
  graphics.ExecuteCommandList(*m_command_list);

  graphics.Swap();
}

void GameMain::OnResize(UINT width,UINT height)
{
  Game::OnResize(width,height);
  
  // resize the viewports
  /*D3D11_Core& graphics = GetGraphics();
  D3D11_VIEWPORT full_viewport = graphics.GetDefaultViewport();
  D3D11_VIEWPORT section_viewport = full_viewport;
  section_viewport.Width /= 2;
  section_viewport.Height /= 2;
  m_viewports.SetViewport(0,section_viewport);
  section_viewport.TopLeftX = section_viewport.Width;
  m_viewports.SetViewport(1,section_viewport);
  section_viewport.TopLeftX = 0;
  section_viewport.TopLeftY = section_viewport.Height;
  m_viewports.SetViewport(2,section_viewport);
  section_viewport.TopLeftX = section_viewport.Width;
  m_viewports.SetViewport(3,section_viewport);
  
  // setup the cameras for the viewports
  float aspect_ratio = full_viewport.Width / full_viewport.Height;
  m_cameras[0]->SetAspecRatio(aspect_ratio);
  m_cameras[1]->SetAspecRatio(aspect_ratio);
  m_cameras[2]->SetAspecRatio(aspect_ratio);
  m_cameras[3]->SetAspecRatio(aspect_ratio);*/
}

void GameMain::LoadCube()
{
  GraphicsCore& graphics = GetGraphics();

  RootSignatureConfig* config = RootSignatureConfig::CreateD3D12(2, 1);
  config->SetStageAccess(true, true, false, false, false, true, false);
  config->SetParamAsConstantBufferView(0, 0, 0, SHADER_VISIBILITY_VERTEX);
  config->SetParamAsDescriptorTable(1, 1, SHADER_VISIBILITY_PIXEL);
  config->SetRangeAsShaderResourceView(1, 0, 1, 0, 0);
  config->SetSampler(0, TEXTURE_FILTER_MIN_MAG_MIP_LINEAR, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, TEXTURE_ADDRESS_MODE_WRAP, 0, 1, COMPARISON_FUNC_NEVER, BORDER_COLOR_TRANSPARENT_BLACK,
    0, 0, 0, 0, SHADER_VISIBILITY_PIXEL);
  m_root_sig = RootSignature::CreateD3D12(graphics, *config);
  if (m_root_sig == NULL)
  {
    exit(1);
  }

  m_vertex_shader = Shader::LoadD3D12("basic_shader_vs_test.cso");
  if (m_vertex_shader == NULL)
  {
    exit(1);
  }
  m_pixel_shader = Shader::LoadD3D12("basic_shader_ps_test.cso");
  if (m_pixel_shader == NULL)
  {
    exit(1);
  }

  m_input_layout = InputLayout::CreateD3D12(3);
  m_input_layout->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
  m_input_layout->SetNextElement(SEM_TEXCOORD, 0, R32G32_FLOAT, 0, false);
  m_input_layout->SetNextElement(SEM_TEXCOORD, 1, R32G32B32_FLOAT, 1, true, 1);

  RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
  rtv_config->SetAlphaToCoverageEnable(false);
  rtv_config->SetIndependentBlendEnable(false);
  rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
  m_pipeline = Pipeline::CreateD3D12(graphics, *m_input_layout, TOPOLOGY_TRIANGLE, *m_vertex_shader, *m_pixel_shader, *rtv_config, *m_root_sig);
  if (m_pipeline == NULL)
  {
    exit(1);
  }

  m_command_list = CommandList::CreateD3D12Direct(graphics, m_pipeline);

  // create the scissor rect that matches the viewport
  Viewport full_viewport = graphics.GetDefaultViewport();
  m_scissor_rect = ViewportToScissorRect(graphics.GetDefaultViewport());

  // setup the cameras for the viewports
  m_camera = new Camera(full_viewport.width / full_viewport.height, XMFLOAT4(  0, 0, -10, 1), XMFLOAT4( 0,  0, 1, 0), XMFLOAT4(0, 1,  0, 0));

  // create the resource heap
  UINT constant_buffer_size = ConstantBuffer::GetAlignedSize(graphics, sizeof(XMMATRIX));
  m_resource_heap = BufferResourceHeap::CreateD3D12(graphics, constant_buffer_size);
  if (m_resource_heap == NULL)
  {
    exit(1);
  }

  // create the descriptor heap
  m_shader_buffer_heap = ShaderResourceDescHeap::CreateD3D12(graphics, 1);
  if (m_shader_buffer_heap == NULL)
  {
    exit(1);
  }

  // create the vertex buffer
  Vertex_PositionTexture vertices[] =
  {
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f), XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f), XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f), XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f), XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f), XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f), XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f), XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f), XMFLOAT2(0.0f,1.0f) },
  };
  m_verts = VertexBuffer_PositionTexture::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
  if (m_verts == NULL)
  {
    exit(1);
  }

  // create the index buffer
  WORD indices[] =
  {
    3, 1, 0,
    2, 1, 3,

    6, 4, 5,
    7, 4, 6,

    11, 9, 8,
    10, 9, 11,

    14, 12, 13,
    15, 12, 14,

    19, 17, 16,
    18, 17, 19,

    22, 20, 21,
    23, 20, 22
  };
  m_indices = IndexBuffer16::CreateD3D12(graphics, ARRAYSIZE(indices), indices);
  if (m_indices == NULL)
  {
    exit(1);
  }

  // create the instance buffer
  XMFLOAT3 instance_pos[] =
  {
    XMFLOAT3(-2, 0, 0),
    XMFLOAT3( 2, 0, 0),
  };

  // combine the vertex and instance buffer
  m_vert_array = VertexBufferArray::CreateD3D12(1);
  m_vert_array->Set(0, *m_verts);

  // create the heap array
  m_heap_array = HeapArray::CreateD3D12(1);
  m_heap_array->SetHeap(0, *m_shader_buffer_heap);

  // create the constant buffer
  m_constant_buffer = ConstantBuffer::CreateD3D12(graphics, *m_resource_heap, *m_shader_buffer_heap, constant_buffer_size);
  if (m_constant_buffer == NULL)
  {
    exit(1);
  }

  // upload the wvp matrix for the camera to the constant buffer
  XMMATRIX tmp;
  XMMATRIX wvp = XMMatrixIdentity();
  m_camera->GetView(tmp);
  wvp *= tmp;
  m_camera->GetProj(tmp);
  wvp *= tmp;
  wvp = XMMatrixTranspose(wvp);
  m_constant_buffer->Upload(&wvp, 0, sizeof(wvp));
  graphics.WaitOnFence();
}
