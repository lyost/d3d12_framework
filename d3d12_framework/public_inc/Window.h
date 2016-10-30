#ifndef WINDOW_H
#define WINDOW_H

#include <windows.h>
#include <map>
#include "Input/KeyboardState.h"
#include "Input/MouseState.h"

/// <summary>
/// Takes care of creation and management of top-level windows for the
/// application
/// </summary>
class Window
{
  public:
    ~Window();
    
    /// <summary>
    /// Creates a default overlapped window
    /// </summary>
    /// <remarks>
    /// The resize handler args could be pushed to a separate function for
    /// setting them, but for the laziness of avoiding an if statement in
    /// WndProc and it being the only handler, they are specified here and the
    /// handler function pointer is not allowed to be NULL.
    /// </remarks>
    /// <param name="title">
    /// title for the window
    /// </param>
    /// <param name="resize_handler">
    /// pointer to the function to call on resize events.  Must be a valid
    /// function pointer (i.e. not NULL), it is up to the caller to ensure this
    /// <remarks>
    /// arguments to this function are: the value specified by arg, the width
    /// of the new client area, and the height of the new client area
    /// </remarks>
    /// </param>
    /// <param name="arg">
    /// caller specified argument to give to the function specified by
    /// resize_handler
    /// </param>
    /// <returns>
    /// pointer to the created window
    /// NULL if an error occurred
    /// </returns>
    static Window* CreateDefaultWindow(WCHAR* title,
      void (*resize_handler)(void*,UINT,UINT),void* arg);
    
    /// <summary>
    /// Retrieves the handle for the window
    /// </summary>
    HWND& GetHandle();
    
    /// <summary>
    /// Shows or hides the mouse pointer
    /// </summary>
    /// <param name="show">
    /// true if the mouse pointer should be shown
    /// false if the mouse pointer should be hidden
    /// </param>
    void ShowMousePointer(bool show);
    
    /// <summary>
    /// Constrains the mouse pointer to this window, or releases the constraint
    /// </summary>
    /// <remarks>
    /// Due to alt-tabbing away from the window automatically releasing the constraint, the
    /// Window instance doesn't keep track if the constraint was previously applied and will
    /// apply it every time the function is called with "constraint" set to true.
    /// </remarks>
    /// <param name="constraint">
    /// true if the mouse pointer should be constrained to this window
    /// false if the mouse pointer should be not be constrained
    /// </param>
    /// <returns>
    /// true if the mouse is constrained
    // false otherwise
    /// </returns>
    bool ConstrainMousePointer(bool constraint);
    
    /// <summary>
    /// Resizes the window
    /// </summary>
    /// <param name="width">
    /// width of the new client area, in pixels 
    /// </param>
    /// <param name="height">
    /// height of the new client area, in pixels
    /// </param>
    void Resize(int width,int height);
    
    /// <summary>
    /// Retrieves the dimensions of the window's client area
    /// </summary>
    /// <param name="width">
    /// where to put the retrieved width
    /// </param>
    /// <param name="height">
    /// where to put the retrieved height
    /// </param>
    void GetWindowClientDim(UINT& width,UINT& height) const;
    
    /// <summary>
    /// Retrieves the desktop's dimensions in pixels
    /// <summary>
    /// <param name="width">
    /// where to put the desktop width
    /// </param>
    /// <param name="height">
    /// where to put the desktop height
    /// </param>
    /// <returns>
    /// true  if the desktop size was determined
    /// false otherwise
    /// </returns>
    bool GetDesktopSize(UINT& width,UINT& height) const;
    
    /// <summary>
    /// Retrieves the current mouse state
    /// </summary>
    /// <returns>
    /// current mouse state
    /// </returns>
    const MouseState& GetMouseState() const;
    
    /// <summary>
    /// Retrieves the current keyboard state
    /// </summary>
    /// <returns>
    /// current keyboard state
    /// </returns>
    const KeyboardState& GetKeyboardState() const;
    
  private:
    // disabled
    Window(const Window& cpy);
    Window& operator=(const Window& cpy);
    
    // used by static Create functions
    Window();
    
#ifndef PUBLIC_HEADER
    /// <summary>
    /// handles various messages sent to the window
    /// </summary>
    /// <remarks>
    /// Since Microsoft recommends window messages over DirectInput for mouse
    /// and keyboard input, this function processes the appropriate messages
    /// for this.  Though support for high DPI mice is currently
    /// not implemented.
    /// </remarks>
    static LRESULT CALLBACK WndProc(HWND wnd,UINT message,WPARAM wparam,
      LPARAM lparam);
#endif /* PUBLIC_HEADER */
    
    /// <summary>
    /// map of handles to window pointers so that WndProc can access individual
    /// window instances (just in case more than one window instance is ever
    /// needed)
    /// </summary>
    static std::map<HWND,Window*> s_wnds;
    
    /// <summary>
    /// handle for the instance used to create the window
    /// </summary>
    HINSTANCE m_instance;
    
    /// <summary>
    /// handle for the window
    /// </summary>
    HWND m_wnd;
    
    /// <summary>
    /// class name for the window, needed to unregister it
    /// </summary>
    LPWSTR m_class_name;
    
    /// <summary>
    /// keeps track of whether the window has been closed or not
    /// </summary>
    bool m_closed;
    
    /// <summary>
    /// state of the keyboard, updated as events are received
    /// </summary>
    KeyboardState m_keyboard;
    
    /// <summary>
    /// state of the mouse, updated as events are received
    /// </summary>
    MouseState m_mouse;
    
    /// <summary>
    /// keeps track of whether the mouse pointer should be visible (true) or
    /// hidden (false)
    /// </summary>
    bool m_mouse_visible;
    
    /// <summary>
    /// function pointer to the resize handler
    /// </summary>
    void (*m_resize_handler)(void*,UINT,UINT);
    
    /// <summary>
    /// the void* arg to provide to m_resize_handler
    /// </summary>
    void* m_arg;
};

#endif /* WINDOW_H */
