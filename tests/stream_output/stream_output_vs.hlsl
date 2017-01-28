struct VertexShaderInput
{
  float4 pos : POSITION;
};

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
};

VertexShaderOutput VS(VertexShaderInput input)
{
  VertexShaderOutput output;

  output.pos = input.pos;

  return output;
}
