#ifndef RENDER_TARGET_H
#define RENDER_TARGET_H

/// <summary>
/// Base class for a render target.  Mutiple render targets are managed by the BackBuffer class.
/// </summary>
/// <remarks>
/// Unlike other most other classes in this library, the user of this library does not create instances of this class.  The appropriate GraphicsCore subclass creates and manages the lifetime of instances
/// of this class.
/// </remarks>
class RenderTarget
{
  public:
    
  protected:
    RenderTarget();
    virtual ~RenderTarget();
    
  private:
    // disabled
    RenderTarget(const RenderTarget& cpy);
    RenderTarget& operator=(const RenderTarget& cpy);
};

#endif /* RENDER_TARGET_H */