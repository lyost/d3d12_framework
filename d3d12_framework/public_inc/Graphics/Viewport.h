#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <windows.h>

/// <summary>
/// Struct for describing viewports
/// </summary>
/// <remarks>
/// Layout must match D3D12_VIEWPORT
/// </remarks>
struct Viewport
{
  float top_left_x;
  float top_left_y;
  float width;
  float height;
  float min_depth;
  float max_depth;
};

/// <summary>
/// Helper function to convert viewports to scissor rects
/// <remarks>
/// todo: move this to the framework library
/// </remarks>
/// </summary>
/// <param name="viewport">
/// viewport to convert
/// </param>
/// <returns>
/// corresponding scissor rect
/// </returns>
RECT ViewportToScissorRect(const Viewport& viewport);

#endif /* VIEWPORT_H */
