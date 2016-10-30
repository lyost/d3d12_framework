#ifndef ROOT_SIGNATURE_H
#define ROOT_SIGNATURE_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/RootSignatureConfig.h"

/// <summary>
/// Root signature (see https://msdn.microsoft.com/en-us/library/windows/desktop/dn899208%28v=vs.85%29.aspx)
/// </summary>
class RootSignature
{
  public:
    /// <summary>
    /// Creates a RootSignature based on the specified config data
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="config">
    /// configuration data for the root signature
    /// </param>
    /// <returns>
    /// pointer to the root signature instance on success
    /// NULL on error
    /// </returns>
    static RootSignature* CreateD3D12(const GraphicsCore& graphics, const RootSignatureConfig& config);

    virtual ~RootSignature();

  protected:
    RootSignature();
    
  private:
    // disabled
    RootSignature(const RootSignature& cpy);
    RootSignature& operator=(const RootSignature& cpy);
};

#endif /* ROOT_SIGNATURE_H */
