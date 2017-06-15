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
  float3 light_dir = normalize(light_pos - input.pos_world);
  float ndotl = max(dot(input.normal, light_dir), 0);
  float3 view_dir = normalize(camera_pos - input.pos_world);
  float3 reflect_dir = reflect(light_pos, input.normal);
  float spec = pow(max(dot(reflect_dir, view_dir), 0), 32);
  return light_color * tex_color * (ambient_intensity + ndotl + spec);
}
