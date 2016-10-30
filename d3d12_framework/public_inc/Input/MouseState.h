#ifndef MOUSE_STATE_H
#define MOUSE_STATE_H

/// <summary>
/// Keeps track of the current state of the mouse
/// </summary>
class MouseState
{
  public:
    /// <summary>
    /// enum naming each of the supported mouse buttons
    /// </summary>
    enum Buttons
    {
      LEFT = 0,
      MIDDLE,
      RIGHT,
      X1,
      X2,
      BUTTONS_MAX // not a button, just the last entry in the enum
    };
    
    MouseState();
    
    /// <summary>
    /// Sets the position of the mouse relative to the upper-left corner of the
    /// of the client area
    /// </summary>
    /// <param name="x">
    /// x position of the mouse
    /// </param>
    /// <param name="y">
    /// y position of the mouse
    /// </param>
    void SetPos(int x,int y);
    
    /// <summary>
    /// Changes the horizontal scroll wheel amount
    /// </summary>
    /// <param name="delta">
    /// amount to adjust the wheel amount by
    /// </param>
    void AdjustWheelX(int delta);
    
    /// <summary>
    /// Changes the vertical scroll wheel amount
    /// </summary>
    /// <param name="delta">
    /// amount to adjust the wheel amount by
    /// </param>
    void AdjustWheelY(int delta);
    
    /// <summary>
    /// Sets the specified mouse button as pressed
    /// </summary>
    /// <param name="button">
    /// which button to set as pressed
    /// </param>
    void SetButtonDown(Buttons button);
    
    /// <summary>
    /// Sets the specified mouse button as not pressed
    /// </summary>
    /// <param name="button">
    /// which button to set as not pressed
    /// </param>
    void SetButtonUp(Buttons button);
    
    /// <summary>
    /// Retrieves the x position of the mouse relative to the upper-left corner
    /// of the client area
    /// </summary>
    /// <returns>
    /// x position of the mouse
    /// </returns>
    int GetXPos() const;
    
    /// <summary>
    /// Retrieves the y position of the mouse relative to the upper-left corner
    /// of the client area
    /// </summary>
    /// <returns>
    /// y position of the mouse
    /// </returns>
    int GetYPos() const;
    
    /// <summary>
    /// Retrieves the amount of movement of the horizontal scroll wheel,
    /// assuming 0 when the window was created
    /// </summary>
    /// <returns>
    /// amount of movement of the horizontal scroll wheel
    /// </returns>
    int GetWheelX() const;
    
    /// <summary>
    /// Retrieves the amount of movement of the vertical scroll wheel, assuming
    /// 0 when the window was created
    /// </summary>
    /// <returns>
    /// amount of movement of the vertical scroll wheel
    /// </returns>
    int GetWheelY() const;
    
    /// <summary>
    /// Retrieves whether the requested mouse button is pressed or not
    /// </summary>
    /// <param name="button">
    /// which button to query for
    /// </param>
    /// <returns>
    /// true if pressed
    /// false otherwise
    /// </returns>
    bool IsButtonPressed(Buttons button) const;
    
  private:
    /// <summary>
    /// x pos of the mouse
    /// </summary>
    int m_x;
    
    /// <summary>
    /// y pos of the mouse
    /// </summary>
    int m_y;
    
    /// <summary>
    /// amount of horizontal scroll
    /// </summary>
    int m_scroll_x;
    
    /// <summary>
    /// amount of vertical scroll
    /// </summary>
    int m_scroll_y;
    
    /// <summary>
    /// state of the various mouse buttons
    /// <remarks>
    /// true = pressed, false = not pressed
    /// </remarks>
    /// </summary>
    bool m_buttons[BUTTONS_MAX];
};

#endif /* MOUSE_STATE_H */