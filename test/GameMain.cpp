#include <vector>
#include "GameMain.h"
#include <directxmath.h>
#include "Graphics/RootSignatureConfig.h"
#include "Graphics/RenderTargetViewConfig.h"
#include "Graphics/RenderTargetViewFormats.h"
#include "Graphics/VertexDeclarations/Vertex_PositionTexture.h"
//#include "Graphics/Shaders/OutputMerger.h"
using namespace std;
using namespace DirectX;

GameMain::GameMain(WCHAR* title)
:Game(title)/*,
 m_instance(NULL),
 m_sampler(NULL),
 m_rtv(NULL),
 m_vert_array(NULL)*/
{
}

GameMain::~GameMain()
{
}

void GameMain::LoadContent()
{
  /*D3D11_Core& graphics = GetGraphics();
  ContentManager& content = GetContentManager();
  
  // change the clear color to grey
  float clear_color[4] = { .3f,.3f,.3f,1 };
  graphics.GetDefaultRenderTargetView().SetClearColor(clear_color);*/
  
  LoadCube();
  Load_RTV_Test();
}

void GameMain::UnloadContent()
{
  delete m_vert_array;
  delete m_instance;
  delete m_indices[0];
  delete m_indices[1];
  delete m_verts[0];
  delete m_verts[1];
  delete m_vertex_shader[0];
  delete m_vertex_shader[1];
  delete m_pixel_shader[0];
  delete m_pixel_shader[1];
  delete m_input_layout[0];
  delete m_input_layout[1];
  delete m_pipeline[0];
  delete m_pipeline[1];
  delete m_root_sig;

  /*ContentManager& content = GetContentManager();
  
  for (int i = 0; i < 4; ++i)
  {
    delete m_cameras[i];
  }
  delete m_camera_rtv;
  delete m_texture_view[0];
  delete m_texture_view[1];
  delete m_texture_view[2];
  delete m_rtv;
  delete m_dsv;
  delete m_instance;
  delete m_sampler;
  delete m_verts[0];
  delete m_indices[0];
  delete m_vert_array;
  delete m_verts[1];
  delete m_indices[1];
  content.UnloadTexture(m_texture[0]);
  content.UnloadTexture(m_texture[1]);
  content.UnloadTexture(m_texture[2]);
  content.UnloadTexture(m_texture[3]);
  content.UnloadShader(m_vertex_shader[0]);
  content.UnloadShader(m_pixel_shader[0]);
  content.UnloadShader(m_vertex_shader[1]);
  content.UnloadShader(m_pixel_shader[1]);*/
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
  // todo
  graphics.Swap();
  graphics.WaitOnFence();

  /*D3D11_Core& graphics = GetGraphics();
  
  // only using 1 d3d11 thread, so just get the immediate context
  ID3D11DeviceContext* context = graphics.GetImmediateContext();
  
  graphics.GetDefaultRenderTargetView().Clear(context);
  graphics.GetDefaultDepthStencilView().Clear(context);
  
#if 1
  // apply the shaders
  m_vertex_shader[0]->MakeActive(context);
  m_pixel_shader[0]->MakeActive(context);
  
  // get the vertex arrays and index array ready for rendering
  m_vert_array->MakeActive(context);
  m_indices[0]->MakeActive(context);
  
  // draw the test model in each viewport
  for (UINT i = 0; i < 4; ++i)
  {
    // make the current viewport active
    m_viewports.MakeActive(context,i,1);
    
    // set the wvp matrix for the viewport
    XMMATRIX tmp;
    XMMATRIX wvp = XMMatrixIdentity();
    m_cameras[i]->GetView(tmp);
    wvp *= tmp;
    m_cameras[i]->GetProj(tmp);
    wvp *= tmp;
    wvp = XMMatrixTranspose(wvp);
    m_vertex_shader[0]->SetConstantBuffer(context,0,&wvp);
    m_vertex_shader[0]->UpdateConstantBuffers(context);
    
    // draw
    graphics.DrawInstancedPrimitives(context,
      D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,0,36,0,2);
  }
#else
  XMMATRIX tmp;
  XMMATRIX wvp = XMMatrixIdentity();
  m_camera_rtv->GetView(tmp);
  wvp *= tmp;
  m_camera_rtv->GetProj(tmp);
  wvp *= tmp;
  wvp = XMMatrixTranspose(wvp);
  m_vertex_shader[1]->SetConstantBuffer(context,0,&wvp);
  m_vertex_shader[1]->MakeActive(context);
  m_pixel_shader[1]->MakeActive(context);
  m_verts[1]->MakeActive(context);
  m_indices[1]->MakeActive(context);
  graphics.DrawIndexedPrimitives(context,D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
    0,6);
#endif
  
  // show the frame
  graphics.Swap();*/
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

  m_vertex_shader[0] = Shader::LoadD3D12("basic_shader_vs.cso");
  if (m_vertex_shader[0] == NULL)
  {
    exit(1);
  }
  m_pixel_shader[0] = Shader::LoadD3D12("basic_shader_ps.cso");
  if (m_pixel_shader[0] == NULL)
  {
    exit(1);
  }

  m_input_layout[0] = InputLayout::CreateD3D12(3);
  m_input_layout[0]->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
  m_input_layout[0]->SetNextElement(SEM_TEXCOORD, 0, R32G32_FLOAT, 0, false);
  m_input_layout[0]->SetNextElement(SEM_TEXCOORD, 1, R32G32B32_FLOAT, 1, true, 1);

  RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
  rtv_config->SetAlphaToCoverageEnable(false);
  rtv_config->SetIndependentBlendEnable(false);
  rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
  m_pipeline[0] = Pipeline::CreateD3D12(graphics, *(m_input_layout[0]), TOPOLOGY_TRIANGLE, *(m_vertex_shader[0]), *(m_pixel_shader[0]), *rtv_config, *m_root_sig);
  if (m_pipeline[0] == NULL)
  {
    exit(1);
  }

  // setup the viewports
  Viewport full_viewport = graphics.GetDefaultViewport();
  Viewport section_viewport = full_viewport;
  section_viewport.width /= 2;
  section_viewport.height /= 2;
  m_viewports.SetNextViewport(section_viewport);
  section_viewport.top_left_x = section_viewport.width;
  m_viewports.SetNextViewport(section_viewport);
  section_viewport.top_left_x = 0;
  section_viewport.top_left_y = section_viewport.height;
  m_viewports.SetNextViewport(section_viewport);
  section_viewport.top_left_x = section_viewport.width;
  m_viewports.SetNextViewport(section_viewport);

  // setup the cameras for the viewports
  m_cameras[0] = new Camera(full_viewport.width / full_viewport.height, XMFLOAT4(  0, 0, -10, 1), XMFLOAT4( 0,  0, 1, 0), XMFLOAT4(0, 1,  0, 0));
  m_cameras[1] = new Camera(full_viewport.width / full_viewport.height, XMFLOAT4( 10, 0,   0, 1), XMFLOAT4(-1,  0, 0, 0), XMFLOAT4(0, 1,  0, 0));
  m_cameras[2] = new Camera(full_viewport.width / full_viewport.height, XMFLOAT4(-10, 0,   0, 1), XMFLOAT4( 1,  0, 0, 0), XMFLOAT4(0, 1,  0, 0));
  m_cameras[3] = new Camera(full_viewport.width / full_viewport.height, XMFLOAT4(  0, 10,  0, 1), XMFLOAT4( 0, -1, 0, 0), XMFLOAT4(0, 0, -1, 0));

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
  m_verts[0] = VertexBuffer_PositionTexture::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
  if (m_verts[0] == NULL)
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
  m_indices[0] = IndexBuffer16::CreateD3D12(graphics, ARRAYSIZE(indices), indices);
  if (m_indices[0] == NULL)
  {
    exit(1);
  }

  // create the instance buffer
  XMFLOAT3 instance_pos[] =
  {
    XMFLOAT3(-2, 0, 0),
    XMFLOAT3( 2, 0, 0),
  };
  m_instance = VertexBuffer_Custom::CreateD3D12(graphics, sizeof(instance_pos) / sizeof(XMFLOAT3), sizeof(XMFLOAT3), instance_pos);
  if (m_instance == NULL)
  {
    exit(1);
  }

  // combine the vertex and instance buffer
  m_vert_array = VertexBufferArray::CreateD3D12(2);
  m_vert_array->Set(0, *(m_verts[0]));
  m_vert_array->Set(1, *m_instance);

#if 0
  D3D11_Core& graphics = GetGraphics();
  ContentManager& content = GetContentManager();
  
  vector<UINT> buffer_widths;
  buffer_widths.push_back(sizeof(XMMATRIX));
  
  InputLayout layout(3);
  layout.SetNextElement(SEM_POSITION,0,DXGI_FORMAT_R32G32B32_FLOAT,0,false);
  layout.SetNextElement(SEM_TEXCOORD,0,DXGI_FORMAT_R32G32_FLOAT,   0,false);
  layout.SetNextElement(SEM_TEXCOORD,1,DXGI_FORMAT_R32G32B32_FLOAT,1,true,1);
  
  m_vertex_shader[0] = content.LoadVertexShader(L"basic_shader_vs.cso",layout,
    buffer_widths);
  if (m_vertex_shader[0] == NULL)
  {
    exit(1);
  }
  
  m_pixel_shader[0] = content.LoadPixelShader(L"basic_shader_ps.cso",
    buffer_widths);
  if (m_pixel_shader[0] == NULL)
  {
    exit(1);
  }
  
  // setup the viewports
  D3D11_VIEWPORT full_viewport = graphics.GetDefaultViewport();
  D3D11_VIEWPORT section_viewport = full_viewport;
  section_viewport.Width /= 2;
  section_viewport.Height /= 2;
  m_viewports.SetNextViewport(section_viewport);
  section_viewport.TopLeftX = section_viewport.Width;
  m_viewports.SetNextViewport(section_viewport);
  section_viewport.TopLeftX = 0;
  section_viewport.TopLeftY = section_viewport.Height;
  m_viewports.SetNextViewport(section_viewport);
  section_viewport.TopLeftX = section_viewport.Width;
  m_viewports.SetNextViewport(section_viewport);
  
  // setup the cameras for the viewports
  m_cameras[0] = new Camera(full_viewport.Width / full_viewport.Height,
    XMFLOAT4(0,0,-10,1),XMFLOAT4(0,0,1,0),XMFLOAT4(0,1,0,0));
  m_cameras[1] = new Camera(full_viewport.Width / full_viewport.Height,
    XMFLOAT4(10,0,0,1),XMFLOAT4(-1,0,0,0),XMFLOAT4(0,1,0,0));
  m_cameras[2] = new Camera(full_viewport.Width / full_viewport.Height,
    XMFLOAT4(-10,0,0,1),XMFLOAT4(1,0,0,0),XMFLOAT4(0,1,0,0));
  m_cameras[3] = new Camera(full_viewport.Width / full_viewport.Height,
    XMFLOAT4(0,10,0,1),XMFLOAT4(0,-1,0,0),XMFLOAT4(0,0,-1,0));
  
  // create the vertex buffer
  Vertex_PositionTexture vertices[] =
  {
    { XMFLOAT3(-1.0f, 1.0f,-1.0f),XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f),XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f),XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f),XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f),XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f),XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f),XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f,-1.0f, 1.0f),XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f),XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3(-1.0f,-1.0f,-1.0f),XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f),XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f),XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3( 1.0f,-1.0f, 1.0f),XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f),XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f),XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f),XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3(-1.0f,-1.0f,-1.0f),XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f,-1.0f),XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f,-1.0f),XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f,-1.0f),XMFLOAT2(0.0f,1.0f) },

    { XMFLOAT3(-1.0f,-1.0f, 1.0f),XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 1.0f),XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 1.0f),XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 1.0f),XMFLOAT2(0.0f,1.0f) },
  };
  m_verts[0] = VertexBuffer_PositionTexture::Create(graphics,
    ARRAYSIZE(vertices),vertices);
  if (m_verts[0] == NULL)
  {
    exit(1);
  }
  
  // create the index buffer
  WORD indices[] =
  {
    3,1,0,
    2,1,3,

    6,4,5,
    7,4,6,

    11,9,8,
    10,9,11,

    14,12,13,
    15,12,14,

    19,17,16,
    18,17,19,

    22,20,21,
    23,20,22
  };
  m_indices[0] = IndexBuffer16::Create(graphics,ARRAYSIZE(indices),indices);
  if (m_indices[0] == NULL)
  {
    exit(1);
  }
  
  // create the instance buffer
  XMFLOAT3 instance_pos[] =
  {
    XMFLOAT3(-2,0,0),
    XMFLOAT3( 2,0,0),
  };
  m_instance = InstanceBuffer::Create(graphics,
    sizeof(instance_pos) / sizeof(XMFLOAT3),sizeof(XMFLOAT3),instance_pos);
  if (m_instance == NULL)
  {
    exit(1);
  }
  
  // combine the vertex and instance buffer
  m_vert_array = new VertexBufferArray(2);
  m_vert_array->Set(0,*(m_verts[0]));
  m_vert_array->Set(1,*m_instance);

  // load the test texture
  pair<Texture*,ShaderResourceView*> tex = content.LoadTexture(L"test.dds");
  m_texture[0]      = tex.first;
  m_texture_view[0] = tex.second;
  if (m_texture[0] == NULL)
  {
    exit(1);
  }
  
  // create the texture to switch to
  D3D11_TEXTURE2D_DESC custom_tex_desc;
  custom_tex_desc.Width              = 64;
  custom_tex_desc.Height             = 64;
  custom_tex_desc.MipLevels          = 1;
  custom_tex_desc.ArraySize          = 1;
  custom_tex_desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
  custom_tex_desc.SampleDesc.Count   = 1;
  custom_tex_desc.SampleDesc.Quality = 0;
  // swap the usage and cpu access lines for testing both update
  // implementations
  //custom_tex_desc.Usage              = D3D11_USAGE_DEFAULT;
  custom_tex_desc.Usage              = D3D11_USAGE_DYNAMIC;
  custom_tex_desc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
  //custom_tex_desc.CPUAccessFlags     = 0;
  custom_tex_desc.CPUAccessFlags     = D3D11_CPU_ACCESS_WRITE;
  custom_tex_desc.MiscFlags          = 0;
  Texture2D* custom_tex = content.CreateTexture(&custom_tex_desc,NULL);
  m_texture[1]          = custom_tex;
  m_texture_view[1]     = ShaderResourceView::Create(graphics,*custom_tex,0,1,
    false);
  
  // create the texture sampler
  D3D11_SAMPLER_DESC sample_desc;
  ZeroMemory(&sample_desc,sizeof(sample_desc));
  sample_desc.Filter         = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
  sample_desc.AddressU       = D3D11_TEXTURE_ADDRESS_WRAP;
  sample_desc.AddressV       = D3D11_TEXTURE_ADDRESS_WRAP;
  sample_desc.AddressW       = D3D11_TEXTURE_ADDRESS_WRAP;
  sample_desc.ComparisonFunc = D3D11_COMPARISON_NEVER;
  sample_desc.MinLOD         = 0;
  sample_desc.MaxLOD         = D3D11_FLOAT32_MAX;
  m_sampler = TextureSampler::Create(sample_desc,graphics);
  if (m_sampler == NULL)
  {
    exit(1);
  }
  
  // setup the pixel shader to use the texture and sampler
  m_pixel_shader[0]->UseTexture(m_texture_view[0],0);
  m_pixel_shader[0]->UseTextureSampler(m_sampler,0);
#endif /* 0 */
}

void GameMain::Load_RTV_Test()
{
  GraphicsCore& graphics = GetGraphics();

  m_vertex_shader[1] = Shader::LoadD3D12("rtv_test_shader_vs.cso");
  if (m_vertex_shader[1] == NULL)
  {
    exit(1);
  }
  m_pixel_shader[1] = Shader::LoadD3D12("rtv_test_shader_ps.cso");
  if (m_pixel_shader[1] == NULL)
  {
    exit(1);
  }

  m_input_layout[1] = InputLayout::CreateD3D12(2);
  m_input_layout[1]->SetNextElement(SEM_POSITION, 0, R32G32B32_FLOAT, 0, false);
  m_input_layout[1]->SetNextElement(SEM_TEXCOORD, 0, R32G32_FLOAT, 0, false);

  RenderTargetViewConfig* rtv_config = RenderTargetViewConfig::CreateD3D12(1);
  rtv_config->SetAlphaToCoverageEnable(false);
  rtv_config->SetIndependentBlendEnable(false);
  rtv_config->SetFormat(0, RTVF_R8G8B8A8_UNORM);
  m_pipeline[1] = Pipeline::CreateD3D12(graphics, *(m_input_layout[0]), TOPOLOGY_TRIANGLE, *(m_vertex_shader[0]), *(m_pixel_shader[0]), *rtv_config, *m_root_sig);
  if (m_pipeline[1] == NULL)
  {
    exit(1);
  }

  // create the vertex buffer
  Vertex_PositionTexture vertices[] =
  {
    { XMFLOAT3(-1.0f,-1.0f, 0.0f), XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 0.0f), XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 0.0f), XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 0.0f), XMFLOAT2(0.0f,1.0f) },
  };
  m_verts[1] = VertexBuffer_PositionTexture::CreateD3D12(graphics, ARRAYSIZE(vertices), vertices);
  if (m_verts[1] == NULL)
  {
    exit(1);
  }

  // create the index buffer
  WORD indices[] =
  {
    1, 0, 2,
    2, 0, 3
  };
  m_indices[1] = IndexBuffer16::CreateD3D12(graphics, ARRAYSIZE(indices), indices);
  if (m_indices[1] == NULL)
  {
    exit(1);
  }


#if 0
  D3D11_Core& graphics = GetGraphics();
  ContentManager& content = GetContentManager();
  
  vector<UINT> buffer_widths;
  buffer_widths.push_back(sizeof(XMMATRIX));
  
  InputLayout layout(2);
  layout.SetNextElement(SEM_POSITION,0,DXGI_FORMAT_R32G32B32_FLOAT,0,false);
  layout.SetNextElement(SEM_TEXCOORD,0,DXGI_FORMAT_R32G32_FLOAT,   0,false);
  
  m_vertex_shader[1] = content.LoadVertexShader(L"rtv_test_shader_vs.cso",
    layout,buffer_widths);
  if (m_vertex_shader[1] == NULL)
  {
    exit(1);
  }
  
  m_pixel_shader[1] = content.LoadPixelShader(L"rtv_test_shader_ps.cso",
    buffer_widths);
  if (m_pixel_shader[1] == NULL)
  {
    exit(1);
  }
  
  // create the vertex buffer
  Vertex_PositionTexture vertices[] =
  {
    { XMFLOAT3(-1.0f,-1.0f, 0.0f),XMFLOAT2(0.0f,0.0f) },
    { XMFLOAT3( 1.0f,-1.0f, 0.0f),XMFLOAT2(1.0f,0.0f) },
    { XMFLOAT3( 1.0f, 1.0f, 0.0f),XMFLOAT2(1.0f,1.0f) },
    { XMFLOAT3(-1.0f, 1.0f, 0.0f),XMFLOAT2(0.0f,1.0f) },
  };
  m_verts[1] = VertexBuffer_PositionTexture::Create(graphics,
    ARRAYSIZE(vertices),vertices);
  if (m_verts[1] == NULL)
  {
    exit(1);
  }
  
  // create the index buffer
  WORD indices[] =
  {
    1,0,2,
    2,0,3
  };
  m_indices[1] = IndexBuffer16::Create(graphics,ARRAYSIZE(indices),indices);
  if (m_indices[1] == NULL)
  {
    exit(1);
  }
  
  // create the rtv texture
  D3D11_TEXTURE2D_DESC tex_desc;
  tex_desc.Width              = 64;
  tex_desc.Height             = 64;
  tex_desc.MipLevels          = 1;
  tex_desc.ArraySize          = 1;
  tex_desc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
  tex_desc.SampleDesc.Count   = 1;
  tex_desc.SampleDesc.Quality = 0;
  tex_desc.Usage              = D3D11_USAGE_DEFAULT;
  tex_desc.BindFlags          =
    D3D11_BIND_SHADER_RESOURCE|D3D11_BIND_RENDER_TARGET;
  tex_desc.CPUAccessFlags     = 0;
  tex_desc.MiscFlags          = 0;
  Texture2D* tex = content.CreateTexture(&tex_desc,NULL);
  m_texture[2]      = tex;
  m_texture_view[2] = ShaderResourceView::Create(graphics,*tex,0,1,false);
  
  // create the render target view of the rtv texture
  m_rtv = RenderTargetView::Create(graphics,*tex,0);
  if (m_rtv == NULL)
  {
    exit(1);
  }
  float clear_color[4] = { 0,0,0,1 };
  m_rtv->SetClearColor(clear_color);
  
  // create the depth stencil texture
  tex_desc.Format    = DXGI_FORMAT_D24_UNORM_S8_UINT;
  tex_desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
  tex = content.CreateTexture(&tex_desc,NULL);
  m_texture[3] = tex;
  m_dsv = DepthStencilView::Create(graphics,*tex,0,0);
  if (m_dsv == NULL)
  {
    exit(1);
  }
  
  // create a viewport the same size as the texture
  D3D11_VIEWPORT viewport = graphics.GetDefaultViewport();
  viewport.Width    = (float)tex_desc.Width;
  viewport.Height   = (float)tex_desc.Height;
  viewport.TopLeftX = 0;
  viewport.TopLeftY = 0;
  m_viewports.SetNextViewport(viewport);
  
  // create the rtv camera
  m_camera_rtv = new Camera(tex_desc.Width / (float)tex_desc.Height,
    XMFLOAT4(0,0,-2,1),XMFLOAT4(0,0,1,0),XMFLOAT4(0,1,0,0));
#endif /* 0 */
}
