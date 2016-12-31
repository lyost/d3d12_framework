cbuffer WVP : register(b0)
{
  matrix wvp;
}

struct VertexShaderInput
{
  float4 pos   : POSITION;
  uint   index : SV_InstanceID;
};

struct VertexShaderOutput
{
  float4 pos   : SV_POSITION;
  float3 uvw   : TEXCOORD0;
  uint   index : TEXCOORD1;
};

VertexShaderOutput VS(VertexShaderInput input, float3 instance_pos : TEXCOORD1)
{
  VertexShaderOutput output;

  output.pos   = mul(input.pos + float4(instance_pos, 0), wvp);
  output.uvw   = input.pos.xyz;
  output.index = input.index;

  return output;
}
