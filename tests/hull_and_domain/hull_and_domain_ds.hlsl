cbuffer WVP : register(b0)
{
  matrix wvp;
}

struct HullShaderConstantOutput
{
  float edgeTesselation[4]   : SV_TessFactor;
  float insideTesselation[2] : SV_InsideTessFactor;
};

struct HullShaderOutput
{
  float4 pos : SV_POSITION;
};

struct DomainShaderOutput
{
  float4 pos : SV_POSITION;
};

[domain("quad")]
DomainShaderOutput DS(HullShaderConstantOutput constant_input, float2 uv : SV_DomainLocation, const OutputPatch<HullShaderOutput, 4> patch)
{
  DomainShaderOutput output;

  float4 top_center    = lerp(patch[0].pos, patch[1].pos, uv.x);
  float4 bottom_center = lerp(patch[3].pos, patch[2].pos, uv.x);

  output.pos = lerp(top_center, bottom_center, uv.y);
  output.pos = mul(output.pos, wvp);

  return output;
}
