cbuffer OverrideColor : register(b0)
{
  float4 override_color;
}

struct VertexShaderInput
{
  float4 pos   : POSITION;
  float4 color : COLOR;
};

struct VertexShaderOutput
{
  float4 pos   : SV_POSITION;
  float4 color : COLOR;
};

VertexShaderOutput VS(VertexShaderInput input)
{
  VertexShaderOutput output;
  
  output.pos   = input.pos;
  output.color = override_color;
  
  return output;
}
