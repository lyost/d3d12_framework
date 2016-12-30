struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float2 uv  : TEXCOORD;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  float r = input.uv.x < .5;
  float b = input.uv.y < .5;
  return float4(r,0,b,1);
}
