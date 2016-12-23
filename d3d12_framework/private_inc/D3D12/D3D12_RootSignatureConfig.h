#ifndef D3D12_ROOT_SIGNATURE_CONFIG_H
#define D3D12_ROOT_SIGNATURE_CONFIG_H

#include <d3d12.h>
#include "Graphics/RootSignatureConfig.h"

/// <summary>
/// Configuration for a root signature (see https://msdn.microsoft.com/en-us/library/windows/desktop/dn899208%28v=vs.85%29.aspx)
/// </summary>
/// <remarks>
/// Since these are used to create RootSignature instances, any changes will need the creation of a new RootSignature instance and for that RootSignature to be used in order for the changes to take
/// effect.
/// </remarks>
class D3D12_RootSignatureConfig : public RootSignatureConfig
{
  public:
    /// <summary>
    /// Creates a blank D3D12_RootSignatureConfig with the specified number of parameter entries and sampler entries
    /// </summary>
    /// <param name="num_params">
    /// number of parameters the root signature will have
    /// </param>
    /// <param name="num_sampler">
    /// number of samplers the root signature will have
    /// </param>
    D3D12_RootSignatureConfig(UINT num_params, UINT num_sampler);
    
    ~D3D12_RootSignatureConfig();

    /// <summary>
    /// Sets which stages of the graphics pipeline can access the root signature
    /// </summary>
    /// <param name="ia">
    /// true  if input assembler stage has access
    /// false otherwise
    /// </param>>
    /// <param name="vs">
    /// true  if vertex shader has access
    /// false otherwise
    /// </param>>
    /// <param name="hs">
    /// true  if hull shader has access
    /// false otherwise
    /// </param>>
    /// <param name="ds">
    /// true  if domain shader has access
    /// false otherwise
    /// </param>>
    /// <param name="gs">
    /// true  if geometry shader has access
    /// false otherwise
    /// </param>>
    /// <param name="ps">
    /// true  if pixel shader has access
    /// false otherwise
    /// </param>>
    /// <param name="os">
    /// true  if stream output stage has access
    /// false otherwise
    /// </param>
    void SetStageAccess(bool ia, bool vs, bool hs, bool ds, bool gs, bool ps, bool os);

    /// <summary>
    /// Sets a sampler entry to the associated values
    /// </summary>
    /// <param name="index">
    /// which sampler to set
    /// </param>
    /// <param name="filter">
    /// filtering method when sampling a texture
    /// </param>
    /// <param name="address_u">
    /// how to resolve u texture coordinates outside [0,1]
    /// </param>
    /// <param name="address_v">
    /// how to resolve v texture coordinates outside [0,1]
    /// </param>
    /// <param name="address_w">
    /// how to resolve w texture coordinates outside [0,1]
    /// </param>
    /// <param name="mip_lod_bias">
    /// offset for determining the mipmap level to use
    /// </param>
    /// <param name="max_anisotropy">
    /// for anisotropy filtering, the max filtering value which must be in the range [1,16]
    /// </param>
    /// <param name="compare_func">
    /// how to compare sample data against existing sample data
    /// </param>
    /// <param name="border_color">
    /// when TEXTURE_ADDRESS_MODE_BORDER is used for an address_* argument, what the border color should be
    /// </param>
    /// <param name="min_lod">
    /// minimum lod that is accessible
    /// </param>
    /// <param name="max_lod">
    /// maximum lod that is accessible
    /// </param>
    /// <param name="shader_register">
    /// which register in hlsl the texture is bound to
    /// </param>
    /// <param name="register_space">
    /// the space part of the texture's register binding in hlsl
    /// </param>
    /// <param name="shaders">
    /// which shader or shaders the sampler is visible to
    /// </param>
    void SetSampler(UINT index, TextureFilters filter, TextureAddressMode address_u, TextureAddressMode address_v, TextureAddressMode address_w, float mip_lod_bias, UINT max_anisotropy,
      CompareFuncs compare_func, TextureBorderColor border_color, float min_lod, float max_lod, UINT shader_register, UINT register_space, ShaderVisibility shaders);

    /// <summary>
    /// Sets a parameter entry as a constant with the associated values
    /// </summary>
    /// <param name="param_index">
    /// which parameter to set
    /// </param>
    /// <param name="shader_register">
    /// shader register
    /// </param>
    /// <param name="register_space">
    /// register space
    /// </param>
    /// <param name="num_32bit_values">
    /// number of constants that occupy a single shader slot
    /// </param>
    /// <param name="shaders">
    /// which shader or shaders the parameter is visible to
    /// </param>
    void SetParamAsConstants(UINT param_index, UINT shader_register, UINT register_space, UINT num_32bit_values, ShaderVisibility shaders);

    /// <summary>
    /// Sets a parameter entry as a constant buffer view with the associated values
    /// </summary>
    /// <param name="param_index">
    /// which parameter to set
    /// </param>
    /// <param name="shader_register">
    /// shader register
    /// </param>
    /// <param name="register_space">
    /// register space
    /// </param>
    /// <param name="shaders">
    /// which shader or shaders the parameter is visible to
    /// </param>
    void SetParamAsConstantBufferView(UINT param_index, UINT shader_register, UINT register_space, ShaderVisibility shaders);

    /// <summary>
    /// Sets a parameter entry as a shader resource view with the associated values
    /// </summary>
    /// <param name="param_index">
    /// which parameter to set
    /// </param>
    /// <param name="shader_register">
    /// shader register
    /// </param>
    /// <param name="register_space">
    /// register space
    /// </param>
    /// <param name="shaders">
    /// which shader or shaders the parameter is visible to
    /// </param>
    void SetParamAsShaderResourceView(UINT param_index, UINT shader_register, UINT register_space, ShaderVisibility shaders);

    /// <summary>
    /// Sets a parameter entry as a unordered access view with the associated values
    /// </summary>
    /// <param name="param_index">
    /// which parameter to set
    /// </param>
    /// <param name="shader_register">
    /// shader register
    /// </param>
    /// <param name="register_space">
    /// register space
    /// </param>
    /// <param name="shaders">
    /// which shader or shaders the parameter is visible to
    /// </param>
    void SetParamAsUnorderedAccessView(UINT param_index, UINT shader_register, UINT register_space, ShaderVisibility shaders);

    /// <summary>
    /// Sets a parameter entry as a descriptor table
    /// </summary>
    /// <param name="param_index">
    /// which parameter to set
    /// </param>
    /// <param name="shader_register">
    /// number of ranges that will be in the descriptor table
    /// </param>
    /// <param name="shaders">
    /// which shader or shaders the parameter is visible to
    /// </param>
    void SetParamAsDescriptorTable(UINT param_index, UINT num_ranges, ShaderVisibility shaders);

    /// <summary>
    /// Sets a parameter entry as a constant buffer view with the associated values
    /// </summary>
    /// <param name="param_index">
    /// which parameter to set
    /// </param>
    /// <param name="range_index">
    /// which range in the descriptor table to set
    /// </param>
    /// <param name="num_descriptors">
    /// number of descriptors in the range
    /// </param>
    /// <param name="base_shader_register">
    /// base shader register
    /// </param>
    /// <param name="register_space">
    /// register space
    /// </param>
    void SetRangeAsConstantBufferView(UINT param_index, UINT range_index, UINT num_descriptors, UINT base_shader_register, UINT register_space);

    /// <summary>
    /// Sets a parameter entry as a shader resource view with the associated values
    /// </summary>
    /// <param name="param_index">
    /// which parameter to set
    /// </param>
    /// <param name="range_index">
    /// which range in the descriptor table to set
    /// </param>
    /// <param name="num_descriptors">
    /// number of descriptors in the range
    /// </param>
    /// <param name="base_shader_register">
    /// base shader register
    /// </param>
    /// <param name="register_space">
    /// register space
    /// </param>
    void SetRangeAsShaderResourceView(UINT param_index, UINT range_index, UINT num_descriptors, UINT base_shader_register, UINT register_space);

    /// <summary>
    /// Sets a parameter entry as a unordered access view with the associated values
    /// </summary>
    /// <param name="param_index">
    /// which parameter to set
    /// </param>
    /// <param name="range_index">
    /// which range in the descriptor table to set
    /// </param>
    /// <param name="num_descriptors">
    /// number of descriptors in the range
    /// </param>
    /// <param name="base_shader_register">
    /// base shader register
    /// </param>
    /// <param name="register_space">
    /// register space
    /// </param>
    void SetRangeAsUnorderedAccessView(UINT param_index, UINT range_index, UINT num_descriptors, UINT base_shader_register, UINT register_space);

    /// <summary>
    /// Sets a parameter entry as a unordered access view with the associated values
    /// </summary>
    /// <param name="param_index">
    /// which parameter to set
    /// </param>
    /// <param name="range_index">
    /// which range in the descriptor table to set
    /// </param>
    /// <param name="num_descriptors">
    /// number of descriptors in the range
    /// </param>
    /// <param name="base_shader_register">
    /// base shader register
    /// </param>
    /// <param name="register_space">
    /// register space
    /// </param>
    void SetRangeAsSampler(UINT param_index, UINT range_index, UINT num_descriptors, UINT base_shader_register, UINT register_space);

    /// <summary>
    /// Retrieves the root signature description
    /// </summary>
    /// <returns>
    /// root signature description
    /// </returns>
    const D3D12_ROOT_SIGNATURE_DESC& GetDesc() const;
    
  private:
    // disabled
    D3D12_RootSignatureConfig();
    D3D12_RootSignatureConfig(const D3D12_RootSignatureConfig& cpy);
    D3D12_RootSignatureConfig& operator=(const D3D12_RootSignatureConfig& cpy);

    /// <summary>
    /// D3D12 description of the root signature
    /// </summary>
    D3D12_ROOT_SIGNATURE_DESC m_desc;

    /// <summary>
    /// root param array to set the configuration of
    /// </summary>
    /// <remarks>
    /// since pParameters in m_desc is declared const, keeping a pointer to a mutable version of the same memory
    /// </remarks>
    D3D12_ROOT_PARAMETER* m_params;

    /// <summary>
    /// sampler array to set the configuration of
    /// </summary>
    /// <remarks>
    /// since pStaticSamplers in m_desc is declared const, keeping a pointer to a mutable version of the same memory
    /// </remarks>
    D3D12_STATIC_SAMPLER_DESC* m_samplers;
};

#endif /* D3D12_ROOT_SIGNATURE_CONFIG_H */
