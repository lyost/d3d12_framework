cbuffer WVP : register(b0)
{
  matrix wvp;
}

struct VertexShaderInput
{
  float4 pos : POSITION;
  float  u   : TEXCOORD;
};

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float  u   : TEXCOORD;
};

VertexShaderOutput VS(VertexShaderInput input)
{
  VertexShaderOutput output;

  output.pos = mul(input.pos, wvp);
  output.u   = input.u;

  return output;
}
