#include "Graphics/Viewports.h"

Viewports::Viewports()
:m_next(0)
{
}

Viewports::~Viewports()
{
}

bool Viewports::SetNextViewport(const Viewport& viewport)
{
  if (m_next >= MAX_VIEWPORTS)
  {
    return false;
  }
  else
  {
    m_viewports[m_next++] = viewport;
    return true;
  }
}

bool Viewports::SetViewport(UINT index, const Viewport& viewport)
{
  if (index >= m_next)
  {
    return false;
  }
  else
  {
    m_viewports[index] = viewport;
    return true;
  }
}

bool Viewports::GetViewport(UINT index, Viewport& viewport) const
{
  if (index >= m_next)
  {
    return false;
  }
  else
  {
    viewport = m_viewports[index];
    return true;
  }
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
