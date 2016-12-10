Texture1D tex1 : register(t0);
Texture2D tex2 : register(t1);
Texture3D tex3 : register(t2);
SamplerState tex_sampler : register(s0);

cbuffer TexturingMode : register(b1)
{
  uint mode;
}

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float3 uvw : TEXCOORD;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  if (mode == 0)
  {
    return tex1.Sample(tex_sampler, input.uvw.x);
  }
  else if (mode == 1)
  {
    return tex2.Sample(tex_sampler, input.uvw.xy);
  }
  else
  {
    return tex3.Sample(tex_sampler, input.uvw);
  }
}
