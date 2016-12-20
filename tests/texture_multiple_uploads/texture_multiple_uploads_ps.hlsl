Texture1DArray tex1 : register(t0);
Texture2DArray tex2 : register(t1);
SamplerState tex_sampler : register(s0);

cbuffer TexturingMode : register(b1)
{
  uint mode;
}

struct VertexShaderOutput
{
  float4 pos   : SV_POSITION;
  float2 uv    : TEXCOORD0;
  uint   index : TEXCOORD1;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  if (mode == 0)
  {
    return tex1.Sample(tex_sampler, float2(input.uv.x, input.index));
  }
  else
  {
    return tex2.Sample(tex_sampler, float3(input.uv.xy, input.index));
  }
}
