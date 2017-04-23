struct VertexShaderOutput
{
  float4 pos   : SV_POSITION;
  float4 color : COLOR;
};

float4 PS(VertexShaderOutput input) : SV_Target
{
  return input.color;
}
