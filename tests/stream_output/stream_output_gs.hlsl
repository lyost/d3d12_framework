cbuffer WVP : register(b0)
{
  matrix wvp;
}

struct ShaderInput
{
  float4 pos : SV_POSITION;
};

struct ShaderOutput
{
  float4 raw_pos : POSITION;
  float4 pos     : SV_POSITION;
};

[maxvertexcount(12)]
void GS(triangle ShaderInput input[3], inout TriangleStream<ShaderOutput> output_stream)
{
  ShaderOutput tmp;

  tmp.raw_pos = input[0].pos;
  tmp.pos = mul(input[0].pos, wvp);
  output_stream.Append(tmp);
  tmp.raw_pos = input[1].pos;
  tmp.pos = mul(input[1].pos, wvp);
  output_stream.Append(tmp);
  tmp.raw_pos = input[2].pos;
  tmp.pos = mul(input[2].pos, wvp);
  output_stream.Append(tmp);
  output_stream.RestartStrip();
}
