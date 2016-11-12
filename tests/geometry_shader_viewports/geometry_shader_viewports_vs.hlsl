struct ShaderInputOutput
{
  float4 pos : POSITION;
  float2 uv  : TEXCOORD;
};

ShaderInputOutput VS(ShaderInputOutput input, float3 instance_pos : TEXCOORD1)
{
  ShaderInputOutput output;

  output.pos = input.pos + float4(instance_pos, 0);
  output.uv  = input.uv;

  return output;
}
