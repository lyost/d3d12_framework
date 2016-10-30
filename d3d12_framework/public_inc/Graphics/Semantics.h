#ifndef SEMANTICS_H
#define SEMANTICS_H

/// <summary>
/// Enum of the various semantics
/// </summary>
/// <remarks>
/// semantic indices are not included in this enum
/// </remarks>
enum Semantics
{
  SEM_BINORMAL,
  SEM_BLENDINDICES,
  SEM_BLENDWEIGHT,
  SEM_COLOR,
  SEM_DEPTH,
  SEM_FOG,
  SEM_NORMAL,
  SEM_POSITION,
  SEM_POSITIONT,
  SEM_PSIZE,
  SEM_TANGENT,
  SEM_TESSFACTOR,
  SEM_TEXCOORD,
  SEM_VFACE,
  SEM_VPOS,
  SEM_SV_CLIPDISTANCE,
  SEM_SV_CULLDISTANCE,
  SEM_SV_COVERAGE,
  SEM_SV_DEPTH,
  SEM_SV_DISPATCHTHREADID,
  SEM_SV_DOMAINLOCATION,
  SEM_SV_GROUPID,
  SEM_SV_GROUPINDEX,
  SEM_SV_GROUPTHREADID,
  SEM_SV_GSINSTANCEID,
  SEM_SV_INSIDETESSFACTOR,
  SEM_SV_ISFRONTFACE,
  SEM_SV_OUTPUTCONTROLPOINTID,
  SEM_SV_POSITION,
  SEM_SV_RENDERTARGETARRAYINDEX,
  SEM_SV_SAMPLEINDEX,
  SEM_SV_TARGET,
  SEM_SV_TESSFACTOR,
  SEM_SV_VIEWPORTARRAYINDEX,
  SEM_SV_INSTANCEID,
  SEM_SV_PRIMITIVEID,
  SEM_SV_VERTEXID
};

/// <summary>
/// Converts entries of the Semantics enum to the string form of their name
/// </summary>
/// <param name="sem">
/// entry in Semantics to convert
/// </param>
/// <returns>
/// the corresponding string
/// </returns>
const char* GetSemanticName(Semantics sem);

#endif /* SEMANTICS_H */
