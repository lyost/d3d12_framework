cbuffer WVP : register(b0)
{
  matrix wvp;
}

struct VertexShaderInput
{
  float4 pos   : POSITION;
  float3 uvw   : TEXCOORD;
  uint   index : SV_InstanceID;
};

struct VertexShaderOutput
{
  float4 pos      : SV_POSITION;
  float3 uvw      : TEXCOORD0;
  float3 cube_uvw : TEXCOORD1;
  uint   index    : TEXCOORD2;
};

VertexShaderOutput VS(VertexShaderInput input, float3 instance_pos : TEXCOORD1)
{
  VertexShaderOutput output;
  
  output.pos      = mul(input.pos + float4(instance_pos, 0), wvp);
  output.uvw      = input.uvw;
  output.cube_uvw = input.pos.xyz;
  output.index    = input.index;
  
  return output;
}
