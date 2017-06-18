Texture2D    tex         : register(t0);
SamplerState tex_sampler : register(s0);

cbuffer LightingData : register(b0)
{
  float3 light_pos;
  float3 camera_pos;
}

struct VertexShaderOutput
{
  float4 pos       : SV_POSITION;
  float2 uv        : TEXCOORD0;
  float3 pos_world : TEXCOORD1;
  float3 normal    : NORMAL;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  const float4 light_color = float4(1, 1, 1, 1);
  const float4 tex_color = tex.Sample(tex_sampler, input.uv);
  const float ambient_intensity = 0.1;
  return light_color * tex_color * ambient_intensity;
}
