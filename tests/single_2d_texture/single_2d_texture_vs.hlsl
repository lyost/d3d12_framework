struct VertexShaderInput
{
  float4 pos : POSITION;
  float2 uv  : TEXCOORD;
};

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float2 uv  : TEXCOORD;
};

VertexShaderOutput VS(VertexShaderInput input)
{
  VertexShaderOutput output;
  
  output.pos   = input.pos;
  output.uv = input.uv;
  
  return output;
}
