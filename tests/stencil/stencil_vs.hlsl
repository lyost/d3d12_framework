cbuffer WVP : register(b0)
{
  matrix world;
  matrix view;
  matrix projection;
}

struct VertexShaderInput
{
  float4 pos    : POSITION;
  float2 uv     : TEXCOORD;
  float3 normal : NORMAL;
};

struct VertexShaderOutput
{
  float4 pos       : SV_POSITION;
  float2 uv        : TEXCOORD0;
  float4 pos_world : TEXCOORD1;
  float3 normal    : NORMAL;
};

VertexShaderOutput VS(VertexShaderInput input)
{
  VertexShaderOutput output;

  output.pos_world = mul(input.pos, world);
  output.pos       = mul(input.pos, transpose(mul(mul(projection, view), world)));
  output.uv        = input.uv;
  output.normal    = input.normal;

  return output;
}
