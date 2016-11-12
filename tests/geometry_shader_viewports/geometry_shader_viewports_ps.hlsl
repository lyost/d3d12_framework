Texture2D tex : register(t0);
SamplerState tex_sampler : register(s0);

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float2 uv  : TEXCOORD;
};

Texture2D    color_tex     : register(t0);
SamplerState color_sampler : register(s0);

float4 PS(VertexShaderOutput input) : SV_Target
{
  return color_tex.Sample(color_sampler, input.uv);
}
