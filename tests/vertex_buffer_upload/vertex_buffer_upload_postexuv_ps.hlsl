Texture2D    tex         : register(t0);
SamplerState tex_sampler : register(s0);

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float2 uv  : TEXCOORD;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  return tex.Sample(tex_sampler, input.uv);
}
