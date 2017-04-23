cbuffer WVP : register(b0)
{
  matrix wvp;
}

struct VertexShaderInput
{
  float4 pos : POSITION;
  float3 uvw : TEXCOORD;
};

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float3 uvw : TEXCOORD;
};

VertexShaderOutput VS(VertexShaderInput input)
{
  VertexShaderOutput output;

  output.pos = mul(input.pos, wvp);
  output.uvw = input.uvw;

  return output;
}
