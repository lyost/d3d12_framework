#ifndef BACK_BUFFER_H
#define BACK_BUFFER_H

class RenderTarget;
#include "Graphics/Buffers/RenderTarget.h"

/// <summary>
/// Manages the back buffers
/// </summary>
/// <remarks>
/// Unlike other most other classes in this library, the user of this library does not create instances of this class.  The appropriate GraphicsCore subclass creates and manages the lifetime of instances
/// of this class.
/// </remarks>
class BackBuffers
{
  public:
    /// <summary>
    /// Updates which render target will be rendered to next
    /// </summary>
    virtual void UpdateCurrentRenderTarget() = 0;

    /// <summary>
    /// Retrieves the current render target
    /// </summary>
    virtual const RenderTarget& GetCurrentRenderTarget() const = 0;
    
  protected:
    BackBuffers();
    virtual ~BackBuffers();
    
  private:
    // disabled
    BackBuffers(const BackBuffers& cpy);
    BackBuffers& operator=(const BackBuffers& cpy);
};

#endif /* BACK_BUFFER_H */