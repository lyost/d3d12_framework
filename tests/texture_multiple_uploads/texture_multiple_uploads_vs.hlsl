cbuffer WVP : register(b0)
{
  matrix wvp;
}

struct VertexShaderInput
{
  float4 pos   : POSITION;
  float2 uv    : TEXCOORD;
  uint   index : SV_InstanceID;
};

struct VertexShaderOutput
{
  float4 pos   : SV_POSITION;
  float2 uv    : TEXCOORD0;
  uint   index : TEXCOORD1;
};

VertexShaderOutput VS(VertexShaderInput input, float3 instance_data : TEXCOORD1)
{
  VertexShaderOutput output;

  output.pos   = mul(input.pos + float4(instance_data, 0), wvp);
  output.uv    = input.uv;
  output.index = input.index;
  
  return output;
}
