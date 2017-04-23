Texture1D    tex         : register(t0);
SamplerState tex_sampler : register(s0);

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float  u   : TEXCOORD;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  return tex.Sample(tex_sampler, input.u);
}
