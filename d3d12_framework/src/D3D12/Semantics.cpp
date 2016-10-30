#include "Graphics/Semantics.h"

const char* GetSemanticName(Semantics sem)
{
  static const char* convert[] =
  {
    "BINORMAL",
    "BLENDINDICES",
    "BLENDWEIGHT",
    "COLOR",
    "DEPTH",
    "FOG",
    "NORMAL",
    "POSITION",
    "POSITIONT",
    "PSIZE",
    "TANGENT",
    "TESSFACTOR",
    "TEXCOORD",
    "VFACE",
    "VPOS",
    "SV_ClipDistance",
    "SV_CullDistance",
    "SV_Coverage",
    "SV_Depth",
    "SV_DispatchThreadID",
    "SV_DomainLocation",
    "SV_GroupID",
    "SV_GroupIndex",
    "SV_GroupThreadID",
    "SV_GSInstanceID",
    "SV_InsideTessFactor",
    "SV_IsFrontFace",
    "SV_OutputControlPointID",
    "SV_Position",
    "SV_RenderTargetArrayIndex",
    "SV_SampleIndex",
    "SV_Target",
    "SV_TessFactor",
    "SV_ViewportArrayIndex",
    "SV_InstanceID",
    "SV_PrimitiveID",
    "SV_VertexID"
  };
  
  return convert[sem];
}
