#ifndef D3D12_LIMITS_H
#define D3D12_LIMITS_H

#include <windows.h>

/// <summary>
/// Maximum number of output streams that can be bound to the stream output stage at the same time
/// </summary>
const UINT MAX_OUTPUT_STREAMS = 4;

/// <summary>
/// Maximum number of render targets that can be bound to the output-merger stage at the same time
/// </summary>
const UINT MAX_RENDER_TARGETS = 8;

#endif /* D3D12_LIMITS_H */
