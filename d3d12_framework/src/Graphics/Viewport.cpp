#include "Graphics/Viewport.h"

RECT ViewportToScissorRect(const Viewport& viewport)
{
  RECT back;

  back.top    = (long)viewport.top_left_y;
  back.left   = (long)viewport.top_left_x;
  back.bottom = (long)(viewport.top_left_y + viewport.height);
  back.right  = (long)(viewport.top_left_x + viewport.width);

  return back;
}