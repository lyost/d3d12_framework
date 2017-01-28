struct PixelShaderInput
{
  float4 raw_pos : POSITION;
  float4 pos     : SV_POSITION;
};

float4 PS(PixelShaderInput input) : SV_Target
{
  return float4(0, 0, 0, 1);
}
