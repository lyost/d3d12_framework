#ifndef D3D12_ROOT_SIGNATURE_H
#define D3D12_ROOT_SIGNATURE_H

#include <d3d12.h>
#include "Graphics/RootSignature.h"

/// <summary>
/// Root signature (see https://msdn.microsoft.com/en-us/library/windows/desktop/dn899208%28v=vs.85%29.aspx)
/// </summary>
class D3D12_RootSignature : public RootSignature
{
  public:
    /// <summary>
    /// Creates a D3D12_RootSignature based on the specified config data
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="config">
    /// configuration data for the root signature
    /// </param>
    /// <returns>
    /// pointer to the root signature config instance on success
    /// NULL on error
    /// </returns>
    static D3D12_RootSignature* Create(const GraphicsCore& graphics, const RootSignatureConfig& config);
    
    ~D3D12_RootSignature();

    ID3D12RootSignature* GetRootSignature() const;
    
  private:
    D3D12_RootSignature(ID3D12RootSignature* root_sig);

    // disabled
    D3D12_RootSignature();
    D3D12_RootSignature(const D3D12_RootSignature& cpy);
    D3D12_RootSignature& operator=(const D3D12_RootSignature& cpy);

    /// <summary>
    /// D3D12 root signature
    /// </summary>
    ID3D12RootSignature* m_root_sig;
};

#endif /* D3D12_ROOT_SIGNATURE_H */
