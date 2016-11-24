#include <sstream>
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_RootSignature.h"
#include "private_inc/D3D12/D3D12_RootSignatureConfig.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

/*void dump_root_sig_config(const D3D12_ROOT_SIGNATURE_DESC& desc)
{
  std::ostringstream out;
  UINT i;

  out << "Flags: " << desc.Flags << '\n'
    << "Num params: " << desc.NumParameters << '\n';
  for (i = 0; i < desc.NumParameters; i++)
  {
    out << "param[" << i << "]:\n"
      << "  type: " << desc.pParameters[i].ParameterType << '\n'
      << "  shader visibility: " << desc.pParameters[i].ShaderVisibility << '\n';
    switch (desc.pParameters[i].ParameterType)
    {
    case D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE:
      out << "  table:\n"
        << "    num entries: " << desc.pParameters[i].DescriptorTable.NumDescriptorRanges << '\n';
      {
        for (UINT j = 0; j < desc.pParameters[i].DescriptorTable.NumDescriptorRanges; j++)
        {
          const D3D12_DESCRIPTOR_RANGE& range = desc.pParameters[i].DescriptorTable.pDescriptorRanges[j];
          out << "    entry[" << j << "]: " << "type " << range.RangeType << ", num " << range.NumDescriptors << ", base " << range.BaseShaderRegister << ", reg space " << range.RegisterSpace
            << ", offset " << range.OffsetInDescriptorsFromTableStart << '\n';
        }
      }
      break;

    case D3D12_ROOT_PARAMETER_TYPE_32BIT_CONSTANTS:
      break;

    case D3D12_ROOT_PARAMETER_TYPE_CBV:
      break;

    case D3D12_ROOT_PARAMETER_TYPE_SRV:
      break;

    case D3D12_ROOT_PARAMETER_TYPE_UAV:
      break;

    default:
      out << "  param type invalid\n";
      break;
    }
  }

  out << "Num static samplers: " << desc.NumStaticSamplers << '\n';
  for (i = 0; i < desc.NumStaticSamplers; i++)
  {
    out << "sampler[" << i << "]: \n"
      << "  Filter: " << desc.pStaticSamplers[i].Filter << '\n'
      << "  AddressU: " << desc.pStaticSamplers[i].AddressU << '\n'
      << "  AddressV: " << desc.pStaticSamplers[i].AddressV << '\n'
      << "  AddressW: " << desc.pStaticSamplers[i].AddressW << '\n'
      << "  MipLODBias: " << desc.pStaticSamplers[i].MipLODBias << '\n'
      << "  MaxAnisotropy: " << desc.pStaticSamplers[i].MaxAnisotropy << '\n'
      << "  ComparisonFunc: " << desc.pStaticSamplers[i].ComparisonFunc << '\n'
      << "  BorderColor: " << desc.pStaticSamplers[i].BorderColor << '\n'
      << "  MinLOD: " << desc.pStaticSamplers[i].MinLOD << '\n'
      << "  MaxLOD: " << desc.pStaticSamplers[i].MaxLOD << '\n'
      << "  ShaderRegister: " << desc.pStaticSamplers[i].ShaderRegister << '\n'
      << "  RegisterSpace: " << desc.pStaticSamplers[i].RegisterSpace << '\n'
      << "  ShaderVisibility: " << desc.pStaticSamplers[i].ShaderVisibility << '\n';
  }

  OutputDebugStringA(out.str().c_str());
}*/

D3D12_RootSignature* D3D12_RootSignature::Create(const GraphicsCore& graphics, const RootSignatureConfig& config)
{
  const D3D12_Core& core = (const D3D12_Core&)graphics;
  const D3D12_RootSignatureConfig& conf = (const D3D12_RootSignatureConfig&)config;

  ID3DBlob* sig;
  ID3DBlob* err;
  HRESULT rc = D3D12SerializeRootSignature(&conf.GetDesc(), D3D_ROOT_SIGNATURE_VERSION_1, &sig, &err);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to serialize root signature, HRESULT = " << rc;
    throw new FrameworkException(out.str());
  }
  const void* root_data = sig->GetBufferPointer();
  UINT root_len = sig->GetBufferSize();
  ID3D12RootSignature* root_sig;
  rc = core.GetDevice()->CreateRootSignature(0, sig->GetBufferPointer(), sig->GetBufferSize(), IID_PPV_ARGS(&root_sig));
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to create root signature, HRESULT = " << rc;
    throw new FrameworkException(out.str());
  }

  return new D3D12_RootSignature(root_sig, conf.GetDesc().Flags);
}

D3D12_RootSignature::D3D12_RootSignature(ID3D12RootSignature* root_sig, D3D12_ROOT_SIGNATURE_FLAGS stage_acess)
:m_root_sig(root_sig),
 m_stage_access(stage_acess)
{
}

D3D12_RootSignature::~D3D12_RootSignature()
{
  m_root_sig->Release();
}

ID3D12RootSignature* D3D12_RootSignature::GetRootSignature() const
{
  return m_root_sig;
}

D3D12_ROOT_SIGNATURE_FLAGS D3D12_RootSignature::GetStageAccess() const
{
  return m_stage_access;
}
