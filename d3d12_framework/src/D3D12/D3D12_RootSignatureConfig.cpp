#include "private_inc/D3D12/D3D12_RootSignatureConfig.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

D3D12_RootSignatureConfig::D3D12_RootSignatureConfig(UINT num_params, UINT num_sampler)
{
  m_params   = new D3D12_ROOT_PARAMETER[num_params];
  m_samplers = new D3D12_STATIC_SAMPLER_DESC[num_sampler];

  m_desc.Flags             = D3D12_ROOT_SIGNATURE_FLAG_NONE;
  m_desc.NumParameters     = num_params;
  m_desc.NumStaticSamplers = num_sampler;
  m_desc.pParameters       = m_params;
  m_desc.pStaticSamplers   = m_samplers;
}

D3D12_RootSignatureConfig::~D3D12_RootSignatureConfig()
{
  for (UINT i = 0; i < m_desc.NumParameters; i++)
  {
    if (m_desc.pParameters[i].ParameterType == D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
    {
      delete[](m_desc.pParameters[i].DescriptorTable.pDescriptorRanges);
    }
  }

  delete[]m_params;
  delete[]m_samplers;
}

void D3D12_RootSignatureConfig::SetStageAccess(bool ia, bool vs, bool hs, bool ds, bool gs, bool ps, bool os)
{
  m_desc.Flags = D3D12_ROOT_SIGNATURE_FLAG_NONE;
  if (ia)
  {
    m_desc.Flags |= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
  }
  if (!vs)
  {
    m_desc.Flags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_VERTEX_SHADER_ROOT_ACCESS;
  }
  if (!hs)
  {
    m_desc.Flags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_HULL_SHADER_ROOT_ACCESS;
  }
  if (!ds)
  {
    m_desc.Flags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_DOMAIN_SHADER_ROOT_ACCESS;
  }
  if (!gs)
  {
    m_desc.Flags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_GEOMETRY_SHADER_ROOT_ACCESS;
  }
  if (!ps)
  {
    m_desc.Flags |= D3D12_ROOT_SIGNATURE_FLAG_DENY_PIXEL_SHADER_ROOT_ACCESS;
  }
  if (os)
  {
    m_desc.Flags |= D3D12_ROOT_SIGNATURE_FLAG_ALLOW_STREAM_OUTPUT;
  }
}

void D3D12_RootSignatureConfig::SetSampler(UINT index, TextureFilters filter, TextureAddressMode address_u, TextureAddressMode address_v, TextureAddressMode address_w, float mip_lod_bias,
  UINT max_anisotropy, CompareFuncs compare_func, TextureBorderColor border_color, float min_lod, float max_lod, UINT shader_register, UINT register_space, ShaderVisibility shaders)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_desc.NumStaticSamplers)
  {
    throw new FrameworkException("index beyond number of static samplers");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_STATIC_SAMPLER_DESC& sampler = m_samplers[index];
  sampler.Filter                     = (D3D12_FILTER)filter;
  sampler.AddressU                   = (D3D12_TEXTURE_ADDRESS_MODE)address_u;
  sampler.AddressV                   = (D3D12_TEXTURE_ADDRESS_MODE)address_v;
  sampler.AddressW                   = (D3D12_TEXTURE_ADDRESS_MODE)address_w;
  sampler.MipLODBias                 = mip_lod_bias;
  sampler.MaxAnisotropy              = max_anisotropy;
  sampler.ComparisonFunc             = (D3D12_COMPARISON_FUNC)compare_func;
  sampler.BorderColor                = (D3D12_STATIC_BORDER_COLOR)border_color;
  sampler.MinLOD                     = min_lod;
  sampler.MaxLOD                     = max_lod;
  sampler.ShaderRegister             = shader_register;
  sampler.RegisterSpace              = register_space;
  sampler.ShaderVisibility           = (D3D12_SHADER_VISIBILITY)shaders;
}

void D3D12_RootSignatureConfig::SetParamAsConstants(UINT param_index, UINT shader_register, UINT register_space, UINT num_32bit_values, ShaderVisibility shaders)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (param_index >= m_desc.NumParameters)
  {
    throw new FrameworkException("param_index beyond number of parameters");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_ROOT_PARAMETER& param    = m_params[param_index];
  param.ParameterType            = D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS;
  param.Constants.ShaderRegister = shader_register;
  param.Constants.RegisterSpace  = register_space;
  param.Constants.Num32BitValues = num_32bit_values;
  param.ShaderVisibility         = (D3D12_SHADER_VISIBILITY)shaders;
}

void D3D12_RootSignatureConfig::SetParamAsConstantBufferView(UINT param_index, UINT shader_register, UINT register_space, ShaderVisibility shaders)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (param_index >= m_desc.NumParameters)
  {
    throw new FrameworkException("param_index beyond number of parameters");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_ROOT_PARAMETER& param     = m_params[param_index];
  param.ParameterType             = D3D12_ROOT_PARAMETER_TYPE_CBV;
  param.Descriptor.ShaderRegister = shader_register;
  param.Descriptor.RegisterSpace  = register_space;
  param.ShaderVisibility          = (D3D12_SHADER_VISIBILITY)shaders;
}

void D3D12_RootSignatureConfig::SetParamAsShaderResourceView(UINT param_index, UINT shader_register, UINT register_space, ShaderVisibility shaders)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (param_index >= m_desc.NumParameters)
  {
    throw new FrameworkException("param_index beyond number of parameters");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_ROOT_PARAMETER& param     = m_params[param_index];
  param.ParameterType             = D3D12_ROOT_PARAMETER_TYPE_SRV;
  param.Descriptor.ShaderRegister = shader_register;
  param.Descriptor.RegisterSpace  = register_space;
  param.ShaderVisibility          = (D3D12_SHADER_VISIBILITY)shaders;
}

void D3D12_RootSignatureConfig::SetParamAsUnorderedAccessView(UINT param_index, UINT shader_register, UINT register_space, ShaderVisibility shaders)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (param_index >= m_desc.NumParameters)
  {
    throw new FrameworkException("param_index beyond number of parameters");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_ROOT_PARAMETER& param     = m_params[param_index];
  param.ParameterType             = D3D12_ROOT_PARAMETER_TYPE_UAV;
  param.Descriptor.ShaderRegister = shader_register;
  param.Descriptor.RegisterSpace  = register_space;
  param.ShaderVisibility          = (D3D12_SHADER_VISIBILITY)shaders;
}

void D3D12_RootSignatureConfig::SetParamAsDescriptorTable(UINT param_index, UINT num_ranges, ShaderVisibility shaders)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (param_index >= m_desc.NumParameters)
  {
    throw new FrameworkException("param_index beyond number of parameters");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_ROOT_PARAMETER& param               = m_params[param_index];
  param.ParameterType                       = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
  param.DescriptorTable.NumDescriptorRanges = num_ranges;
  param.DescriptorTable.pDescriptorRanges   = new D3D12_DESCRIPTOR_RANGE[num_ranges];
  param.ShaderVisibility                    = (D3D12_SHADER_VISIBILITY)shaders;
}

void D3D12_RootSignatureConfig::SetRangeAsConstantBufferView(UINT param_index, UINT range_index, UINT num_descriptors, UINT base_shader_register, UINT register_space)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (param_index >= m_desc.NumParameters)
  {
    throw new FrameworkException("param_index beyond number of parameters");
  }
  if (m_params[param_index].ParameterType != D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
  {
    throw new FrameworkException("parameter type is not a descriptor table");
  }
  if (range_index >= m_params[param_index].DescriptorTable.NumDescriptorRanges)
  {
    throw new FrameworkException("range_index beyond number of ranges");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_DESCRIPTOR_RANGE* range            = (D3D12_DESCRIPTOR_RANGE*)&m_params[param_index].DescriptorTable.pDescriptorRanges[range_index];
  range->RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_CBV;
  range->NumDescriptors                    = num_descriptors;
  range->BaseShaderRegister                = base_shader_register;
  range->RegisterSpace                     = register_space;
  range->OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

void D3D12_RootSignatureConfig::SetRangeAsShaderResourceView(UINT param_index, UINT range_index, UINT num_descriptors, UINT base_shader_register, UINT register_space)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (param_index >= m_desc.NumParameters)
  {
    throw new FrameworkException("param_index beyond number of parameters");
  }
  if (m_params[param_index].ParameterType != D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
  {
    throw new FrameworkException("parameter type is not a descriptor table");
  }
  if (range_index >= m_params[param_index].DescriptorTable.NumDescriptorRanges)
  {
    throw new FrameworkException("range_index beyond number of ranges");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_DESCRIPTOR_RANGE* range            = (D3D12_DESCRIPTOR_RANGE*)&m_params[param_index].DescriptorTable.pDescriptorRanges[range_index];
  range->RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
  range->NumDescriptors                    = num_descriptors;
  range->BaseShaderRegister                = base_shader_register;
  range->RegisterSpace                     = register_space;
  range->OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

void D3D12_RootSignatureConfig::SetRangeAsUnorderedAccessView(UINT param_index, UINT range_index, UINT num_descriptors, UINT base_shader_register, UINT register_space)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (param_index >= m_desc.NumParameters)
  {
    throw new FrameworkException("param_index beyond number of parameters");
  }
  if (m_params[param_index].ParameterType != D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
  {
    throw new FrameworkException("parameter type is not a descriptor table");
  }
  if (range_index >= m_params[param_index].DescriptorTable.NumDescriptorRanges)
  {
    throw new FrameworkException("range_index beyond number of ranges");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_DESCRIPTOR_RANGE* range            = (D3D12_DESCRIPTOR_RANGE*)&m_params[param_index].DescriptorTable.pDescriptorRanges[range_index];
  range->RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
  range->NumDescriptors                    = num_descriptors;
  range->BaseShaderRegister                = base_shader_register;
  range->RegisterSpace                     = register_space;
  range->OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

void D3D12_RootSignatureConfig::SetRangeAsSampler(UINT param_index, UINT range_index, UINT num_descriptors, UINT base_shader_register, UINT register_space)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (param_index >= m_desc.NumParameters)
  {
    throw new FrameworkException("param_index beyond number of parameters");
  }
  if (m_params[param_index].ParameterType != D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE)
  {
    throw new FrameworkException("parameter type is not a descriptor table");
  }
  if (range_index >= m_params[param_index].DescriptorTable.NumDescriptorRanges)
  {
    throw new FrameworkException("range_index beyond number of ranges");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  D3D12_DESCRIPTOR_RANGE* range            = (D3D12_DESCRIPTOR_RANGE*)&m_params[param_index].DescriptorTable.pDescriptorRanges[range_index];
  range->RangeType                         = D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER;
  range->NumDescriptors                    = num_descriptors;
  range->BaseShaderRegister                = base_shader_register;
  range->RegisterSpace                     = register_space;
  range->OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;
}

const D3D12_ROOT_SIGNATURE_DESC& D3D12_RootSignatureConfig::GetDesc() const
{
  return m_desc;
}
