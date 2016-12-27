#include "Graphics/Viewports.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"

Viewports::Viewports()
:m_next(0)
{
}

Viewports::~Viewports()
{
}

void Viewports::SetNextViewport(const Viewport& viewport)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (m_next >= MAX_VIEWPORTS)
  {
    throw FrameworkException("No more viewports available to be set");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_viewports[m_next++] = viewport;
}

void Viewports::SetViewport(UINT index, const Viewport& viewport)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_next)
  {
    throw FrameworkException("Index beyond the number of used viewports");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_viewports[index] = viewport;
}

void Viewports::GetViewport(UINT index, Viewport& viewport) const
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (index >= m_next)
  {
    throw FrameworkException("Index beyond the number of used viewports");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  viewport = m_viewports[index];
}

UINT Viewports::GetNumInUse() const
{
  return m_next;
}

const Viewport* Viewports::GetViewports() const
{
  return m_viewports;
}

UINT Viewports::GetMaxViewports()
{
  return MAX_VIEWPORTS;
}
