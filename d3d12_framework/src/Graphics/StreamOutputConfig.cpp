#include "Graphics/StreamOutputConfig.h"
#include "private_inc/D3D12/D3D12_StreamOutputConfig.h"

StreamOutputConfig* StreamOutputConfig::CreateD3D12(UINT num_entries)
{
  return new D3D12_StreamOutputConfig(num_entries);
}

StreamOutputConfig::StreamOutputConfig()
{
}

StreamOutputConfig::~StreamOutputConfig()
{
}
