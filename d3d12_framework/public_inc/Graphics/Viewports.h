#ifndef VIEWPORTS_H
#define VIEWPORTS_H

#include <windows.h>
#include "Graphics/Viewport.h"

/// <summary>
/// Takes care of managing viewports
/// </summary>
/// <remarks>
/// Instances of this class manage multiple viewports instead of a single one due to  ID3D12GraphicsCommandList::RSSetViewports taking a number of viewports and a pointer to an array with the
/// specified number of viewports.  It doesn't provide a way to set a single arbitrary viewport at a time.
/// </remarks>
class Viewports
{
  public:
    Viewports();
    ~Viewports();
    
    /// <summary>
    /// Sets the next available viewport to the specified value, and increases the number of viewports in use
    /// </summary>
    /// <param name="viewport">
    /// settings for the new viewport
    /// </param>
    /// <returns>
    /// true  if the viewport was added successfully
    /// false otherwise (i.e. trying to add too many viewports)
    /// </returns>
    bool SetNextViewport(const Viewport& viewport);
    
    /// <summary>
    /// Sets the specified viewport to the specified value
    /// </summary>
    /// <param name="index">
    /// index of the viewport to set
    /// </param>
    /// <param name="viewport">
    /// settings for the viewport
    /// </param>
    /// <returns>
    /// true  if the viewport was updated successfully
    /// false otherwise (i.e. trying to set an unused viewport)
    /// </returns>
    bool SetViewport(UINT index, const Viewport& viewport);
    
    /// <summary>
    /// Retrieves the requested viewport's data
    /// </summary>
    /// <param name="index">
    /// index of the viewport to retrieve
    /// </param>
    /// <param name="viewport">
    /// where to put the viewport's data
    /// </param>
    /// <returns>
    /// true if the viewport could be retrieved
    /// false otherwise
    /// </returns>
    bool GetViewport(UINT index,Viewport& viewport) const;
    
    /// <summary>
    /// Retrieves the number of viewports currently in use
    /// </summary>
    /// <returns>
    /// number of viewports in use
    /// </returns>
    UINT GetNumInUse() const;

    /// <summary>
    /// Retrieves an array of the viewports
    /// </summary>
    /// <returns>
    /// array of the viewports
    /// </returns>
    const Viewport* GetViewports() const;
    
    /// <summary>
    /// Retrieves the maximium number of viewports that can be used by a single instance
    /// </summary>
    /// <returns>
    /// maximium number of viewports that can be used
    /// </returns>
    static UINT GetMaxViewports();
    
  private:
    // disabled
    Viewports(const Viewports& cpy);
    Viewports& operator=(const Viewports& cpy);

    /// <summary>
    /// maximum number of viewports that can be set at once
    /// <remarks>
    /// must match D3D12_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE
    /// </remarks>
    /// </summary>
    enum
    {
      MAX_VIEWPORTS = 16
    };
    
    /// <summary>
    /// array of the various viewports
    /// </summary>
    Viewport m_viewports[MAX_VIEWPORTS];
    
    /// <summary>
    /// index into m_viewports for which viewport is the next one to use
    /// </summary>
    UINT m_next;
};

#endif /* VIEWPORTS_H */
