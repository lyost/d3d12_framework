struct VertexShaderOutput
{
  float4 pos : SV_POSITION;
};

struct HullShaderConstantOutput
{
  float edgeTesselation[4]   : SV_TessFactor;
  float insideTesselation[2] : SV_InsideTessFactor;
};

struct HullShaderOutput
{
  float4 pos : SV_POSITION;
};

HullShaderConstantOutput hsConstantFunc(InputPatch<VertexShaderOutput, 4> input, uint patch_id : SV_PrimitiveID)
{
  HullShaderConstantOutput output;

  output.edgeTesselation[0] = output.edgeTesselation[1] = output.edgeTesselation[2] = output.edgeTesselation[3] = 1;
  output.insideTesselation[0] = output.insideTesselation[1] = 1;

  return output;
}

[domain("quad")]
[partitioning("integer")]
[outputtopology("triangle_ccw")]
[outputcontrolpoints(4)]
[patchconstantfunc("hsConstantFunc")]
HullShaderOutput HS(InputPatch<VertexShaderOutput, 4> input, uint i: SV_OutputControlPointID, uint patch_id : SV_PrimitiveID)
{
  HullShaderOutput output;

  output.pos = input[i].pos;

  return output;
}
