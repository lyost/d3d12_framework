#ifndef COMMAND_LIST_BUNDLE_H
#define COMMAND_LIST_BUNDLE_H

class CommandList;

#include "Graphics/CommandList.h"

/// <summary>
/// Bundle of command lists that are stored in the order they are added
/// </summary>
class CommandListBundle
{
  public:
    /// <summary>
    /// Creates a D3D12 command list bundle
    ///</summary>
    /// <returns>
    /// pointer to the command list bundle on success
    /// NULL otherwise
    /// </returns>
    static CommandListBundle* CreateD3D12();

    virtual ~CommandListBundle();

    /// <summary>
    /// Adds the specified command list to the bundle
    /// </summary>
    /// <param name="list">
    /// command list to add
    /// </param>
    virtual void AddCommandList(const CommandList& list) = 0;

    /// <summary>
    /// Removes the specified command list from the bundle
    /// </summary>
    /// <remarks>
    /// This is an O(n) search to find the list to remove
    /// </remarks>
    /// <param name="list">
    /// which command list to remove
    /// </param>
    virtual void RemoveCommandList(const CommandList& list) = 0;

    /// <summary>
    /// Removes the command list at the specified index from the bundle
    /// </summary>
    /// <param name="index">
    /// index of the command list to remove
    /// </param>
    virtual void RemoveCommandList(UINT index) = 0;

    /// <summary>
    /// Retrieves the number of command lists
    /// </summary>
    /// <returns>
    /// number of command lists
    /// </returns>
    virtual UINT GetNumCommandLists() const = 0;

  protected:
    CommandListBundle();
    
  private:
    // disabled
    CommandListBundle(const CommandListBundle& cpy);
    CommandListBundle& operator=(const CommandListBundle& cpy);
};

#endif /* COMMAND_LIST_BUNDLE_H */
