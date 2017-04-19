struct LookupTableEntry
{
  float left;
  float right;
  float top;
  float bottom;
};

cbuffer LOOKUP_TABLE : register(b0)
{
  LookupTableEntry lookup_table[24];
}

struct VertexShaderInput
{
  float2 pos                : POSITION;
  float3 uv                 : TEXCOORD0;
};

struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
  float2 uv  : TEXCOORD;
};

VertexShaderOutput VS(VertexShaderInput input)
{
  VertexShaderOutput output;

  output.pos  = float4(input.pos.x, input.pos.y, 0, 1);
  output.uv.x = (1 - input.uv.x) * lookup_table[input.uv.z].left + input.uv.x * lookup_table[input.uv.z].right;
  output.uv.y = (1 - input.uv.y) * lookup_table[input.uv.z].top  + input.uv.y * lookup_table[input.uv.z].bottom;

  return output;
}
