TextureCubeArray  tex         : register(t0);
SamplerState      tex_sampler : register(s0);

struct VertexShaderOutput
{
  float4 pos   : SV_POSITION;
  float3 uvw   : TEXCOORD0;
  uint   index : TEXCOORD1;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  return tex.Sample(tex_sampler, float4(input.uvw, input.index));
}
