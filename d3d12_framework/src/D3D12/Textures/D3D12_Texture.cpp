#include <sstream>

#include "private_inc/D3D12/Textures/D3D12_Texture.h"
#include "private_inc/D3D12/D3D12_Core.h"

#include "log.h"

#include "DDSTextureLoader.h"

using namespace std;

Texture* D3D12_Texture::LoadFromFile(GraphicsCore& graphics, const WCHAR* path)
{
  D3D12_Core& core = (D3D12_Core&)graphics;

  ID3D12Resource* texture;
  D3D12_SHADER_RESOURCE_VIEW_DESC tex_view;
  // todo: figure out why this doesn' work
  HRESULT rc = DirectX::CreateDDSTextureFromFile(core.GetDevice(), path, &texture, &tex_view);
  if (FAILED(rc))
  {
    if (log_would_output())
    {
      wstringstream out;
      out << L"Failed to load texture file: " << path << L"\n";
      log_print(out.str().c_str());
    }
    return NULL;
  }
  // todo: is rest of code from https://github.com/LeifNode/D3D12-DDSTextureLoader sample needed?

  return new D3D12_Texture(texture, tex_view);
}

D3D12_Texture::D3D12_Texture(ID3D12Resource* texture, D3D12_SHADER_RESOURCE_VIEW_DESC srv_desc)
:m_texture(texture),
 m_srv_desc(srv_desc)
{
}

D3D12_Texture::~D3D12_Texture()
{
  m_texture->Release();
}

ID3D12Resource* D3D12_Texture::GetResource() const
{
  return m_texture;
}
