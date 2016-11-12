cbuffer WVP : register(b0)
{
  matrix wvp0;
  matrix wvp1;
  matrix wvp2;
  matrix wvp3;
}

struct ShaderInput
{
  float4 pos : POSITION;
  float2 uv  : TEXCOORD;
};

struct ShaderOutput
{
  float4 pos      : SV_POSITION;
  float2 uv       : TEXCOORD;
  uint   viewport : SV_ViewportArrayIndex;
};

[maxvertexcount(12)]
void GS(triangle ShaderInput input[3], inout TriangleStream<ShaderOutput> output_stream)
{
  ShaderOutput tmp;

  tmp.viewport = 0;
  tmp.pos = mul(input[0].pos, wvp0);
  tmp.uv  = input[0].uv;
  output_stream.Append(tmp);
  tmp.pos = mul(input[1].pos, wvp0);
  tmp.uv = input[1].uv;
  output_stream.Append(tmp);
  tmp.pos = mul(input[2].pos, wvp0);
  tmp.uv = input[2].uv;
  output_stream.Append(tmp);
  output_stream.RestartStrip();

  tmp.viewport = 1;
  tmp.pos = mul(input[0].pos, wvp1);
  tmp.uv = input[0].uv;
  output_stream.Append(tmp);
  tmp.pos = mul(input[1].pos, wvp1);
  tmp.uv = input[1].uv;
  output_stream.Append(tmp);
  tmp.pos = mul(input[2].pos, wvp1);
  tmp.uv = input[2].uv;
  output_stream.Append(tmp);
  output_stream.RestartStrip();

  tmp.viewport = 2;
  tmp.pos = mul(input[0].pos, wvp2);
  tmp.uv = input[0].uv;
  output_stream.Append(tmp);
  tmp.pos = mul(input[1].pos, wvp2);
  tmp.uv = input[1].uv;
  output_stream.Append(tmp);
  tmp.pos = mul(input[2].pos, wvp2);
  tmp.uv = input[2].uv;
  output_stream.Append(tmp);
  output_stream.RestartStrip();

  tmp.viewport = 3;
  tmp.pos = mul(input[0].pos, wvp3);
  tmp.uv = input[0].uv;
  output_stream.Append(tmp);
  tmp.pos = mul(input[1].pos, wvp3);
  tmp.uv = input[1].uv;
  output_stream.Append(tmp);
  tmp.pos = mul(input[2].pos, wvp3);
  tmp.uv = input[2].uv;
  output_stream.Append(tmp);
  output_stream.RestartStrip();
}
