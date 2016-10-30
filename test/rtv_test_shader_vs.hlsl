cbuffer WVP : register(b0)
{
  matrix wvp;
}

struct VertexShaderInput
{
  float4 pos : POSITION;
  float2 uv  : TEXCOORD0;
};

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float2 uv  : TEXCOORD0;
};

VertexShaderOutput VS(VertexShaderInput input)
{
  VertexShaderOutput output;
  
  output.pos = mul(input.pos,wvp);
  output.uv = input.uv;
  
  return output;
}
