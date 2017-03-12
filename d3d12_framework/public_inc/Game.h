#ifndef GAME_H
#define GAME_H

#include "Window.h"
#include "Input/KeyboardState.h"
#include "Input/MouseState.h"
#include "Graphics/GraphicsCore.h"

/// <summary>
/// Base class for Game objects that provide the basic framework for a game
/// (i.e. takes care of managing the window, handles time delays for the update
/// cycle, etc)
/// </summary>
class Game
{
  public:
    /// <summary>
    /// Creates the game instance, including the window that will be used for
    /// it
    /// </summary>
    /// <remarks>
    /// A default 640x480 overlapped window is created.  It can be resized or
    /// made full screen by calling the appropriate functions on the instance.
    /// </remarks>
    Game(WCHAR* title);
    
    /// <summary>
    /// Performs any needed cleanup
    /// </summary>
    virtual ~Game();
    
    /// <summary>
    /// Runs the game until it is exited for any reason
    /// </summary>
    void Run();
    
    /// <summary>
    /// Sets whether the game's window should be full screen or not
    /// <remarks>
    /// This tries to preserve the current window's client area dimensions.  If
    /// a different resolution is desired, call Resize first with the updated
    /// resolution.
    /// </remarks>
    /// <summary>
    /// <param name="enable">
    /// true  if the window should be fullscreen
    /// false if the window should be in windowed mode
    /// </param>
    void Fullscreen(bool enable);
    
  protected:
    /// <summary>
    /// Causes the instance to exit its run loop at the end of the current
    /// iteration
    /// </summary>
    void Exit();
    
    /// <summary>
    /// Where subclasses should load their content (graphical or otherwise)
    /// </summary>
    virtual void LoadContent() = 0;
    
    /// <summary>
    /// Where subclasses should unload their content (graphical or otherwise) just before deallocation of the game instance
    /// </summary>
    virtual void UnloadContent() = 0;
    
    /// <summary>
    /// Where subclasses should update their game state
    /// </summary>
    /// <param name="ms">
    /// number of milliseconds since the update
    /// </param>
    virtual void Update(UINT ms) = 0;
    
    /// <summary>
    /// Where subclasses should draw the current frame
    /// </summary>
    /// <param name="ms">
    /// number of milliseconds since the last frame
    /// </param>
    virtual void Draw(UINT ms) = 0;
    
    /// <summary>
    /// Handler for when the window is resized
    /// </summary>
    /// <remarks>
    /// If overridden by a subclass, the base class version must be called to
    /// ensure that base class members are properly updated.
    /// </remarks>
    /// <remarks>
    /// It is strongly recommended for subclasses to override this function at least to update the projection matrix of any cameras, handle resizing of the viewport(s), and catching possible
    /// FrameworkException instances.
    /// </remarks>
    /// <param name="width">
    /// width of the new client area, in pixels 
    /// </param>
    /// <param name="height">
    /// height of the new client area, in pixels
    /// </param>
    /// <exception cref="FrameworkException">
    /// Thrown when an error is encountered
    /// </exception>
    virtual void OnResize(UINT width,UINT height);
    
    /// <summary>
    /// Retrieves the window for the game
    /// </summary>
    /// <returns>
    /// reference to the game's window
    /// </returns>
    Window& GetWindow();
    
    /// <summary>
    /// Retrieves the graphics interface
    /// </summary>
    /// <returns>
    /// reference to the graphics interface
    /// </returns>
    GraphicsCore& GetGraphics();
    
    /// <summary>
    /// Retrieves the number of milliseconds per frame
    /// </summary>
    /// <returns>
    /// number of milliseconds per frame
    /// </returns>
    UINT GetMSPerFrame() const;
    
    /// <summary>
    /// Sets the number of milliseconds per frame
    /// </summary>
    /// <param name="mspf">
    /// number of milliseconds per frame
    /// </returns>
    void SetMSPerFrame(UINT mspf);
    
  private:
    // disabled
    Game(const Game& cpy);
    Game& operator=(const Game& cpy);
    
    /// <summary>
    /// Call back function to provide instances of Window for handling resize
    /// events
    /// </summary>
    /// <param name="arg">
    /// pointer to the Game instance that owns the window that was resized
    /// </param>
    /// <param name="width">
    /// height of the new window client area, in pixels
    /// </param>
    /// <param name="height">
    /// width of the new window client area, in pixels
    /// </param>
    static void ResizeHandler(void* arg,UINT width,UINT height);
    
    /// <summary>
    /// window for the game
    /// </summary>
    Window* m_window;
    
    /// <summary>
    /// whether the Run loop should continue to occur (true) or not (false)
    /// </summary>
    bool m_run;
    
    /// <summary>
    /// graphics core for m_window
    /// </summary>
    GraphicsCore* m_graphics;
    
    /// <summary>
    /// number of milliseconds to wait between frames
    /// </summary>
    /// <remarks>
    /// constructor defaults this to 60 fps
    /// </remarks>
    UINT m_mspf;
};

#endif /* GAME_H */
