#ifndef KEYBOARD_STATE_H
#define KEYBOARD_STATE_H

#include <vector>

/// <summary>
/// Keeps track of the current state of the keyboard
/// </summary>
/// <remarks>
/// key codes are the Windows Virtual Key Codes defined in Winuser.h
/// </remarks>
class KeyboardState
{
  public:
    KeyboardState();
    
    /// <summary>
    /// Sets a key as being pressed
    /// </summary>
    /// <param name="key">
    /// virtual key code for the key
    /// </param>
    /// <param name="extended">
    /// true if this is an extended key
    /// false otherwise
    /// </param>
    void SetKeyDown(int key,bool extended);
    
    /// <summary>
    /// Sets a key as not being pressed
    /// </summary>
    /// <param name="key">
    /// virtual key code for the key
    /// </param>
    /// <param name="extended">
    /// true if this is an extended key
    /// false otherwise
    /// </param>
    void SetKeyUp(int key,bool extended);
    
    /// <summary>
    /// Retrieves whether a key is being pressed or not
    /// </summary>
    /// <param name="key">
    /// virtual key code for the key
    /// </param>
    /// <param name="extended">
    /// true if this is for an extended key
    /// false otherwise
    /// </param>
    /// <returns>
    /// true if the key is being pressed
    /// false otherwise
    /// </returns>
    bool IsKeyDown(int key,bool extended) const;
    
  private:
    /// <summary>
    /// Converts a virtual key code to an index into m_pressed
    /// </summary>
    /// <param name="key">
    /// virtual key code for the key
    /// </param>
    /// <param name="extended">
    /// true if this is for an extended key
    /// false otherwise
    /// </param>
    /// <returns>
    /// corresponding index into m_pressed
    /// </returns>
    std::vector<bool>::size_type ToIndex(int key,bool extended) const;
    
    /// <summary>
    /// keeps track of which keys are pressed
    /// </summary>
    std::vector<bool> m_pressed;
};

#endif /* KEYBOARD_STATE_H */