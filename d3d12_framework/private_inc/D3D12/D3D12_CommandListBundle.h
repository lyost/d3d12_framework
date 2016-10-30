#ifndef D3D12_COMMAND_LIST_BUNDLE_H
#define D3D12_COMMAND_LIST_BUNDLE_H

#include <d3d12.h>
#include <vector>
#include "Graphics/CommandListBundle.h"

/// <summary>
/// D3D12 Command lists bundled together so they can be passed as a unit to ID3D12CommandQueue::ExecuteCommandLists
/// </summary>
class D3D12_CommandListBundle : public CommandListBundle
{
  public:
    /// <summary>
    /// Creates a D3D12 command list bundle
    ///</summary>
    /// <returns>
    /// pointer to the command list bundle on success
    /// NULL otherwise
    /// </returns>
    static D3D12_CommandListBundle* Create();

    ~D3D12_CommandListBundle();

    /// <summary>
    /// Adds the specified command list to the bundle
    /// </summary>
    /// <param name="list">
    /// command list to add
    /// </param>
    void AddCommandList(const CommandList& list);

    /// <summary>
    /// Removes the specified command list from the bundle
    /// </summary>
    /// <remarks>
    /// This is an O(n) search to find the list to remove
    /// </remarks>
    /// <param name="list">
    /// which command list to remove
    /// </param>
    void RemoveCommandList(const CommandList& list);

    /// <summary>
    /// Removes the command list at the specified index from the bundle
    /// </summary>
    /// <param name="index">
    /// index of the command list to remove
    /// </param>
    void RemoveCommandList(UINT index);

    /// <summary>
    /// Retrieves the number of command lists
    /// </summary>
    /// <returns>
    /// number of command lists
    /// </returns>
    UINT GetNumCommandLists() const;

    /// <summary>
    /// Retrieves an array of command lsits
    /// </summary>
    /// <returns>
    /// array of command lists
    /// </returns>
    ID3D12GraphicsCommandList*const* GetCommandLists() const;

  protected:
    D3D12_CommandListBundle();
    
  private:
    // disabled
    D3D12_CommandListBundle(const D3D12_CommandListBundle& cpy);
    D3D12_CommandListBundle& operator=(const D3D12_CommandListBundle& cpy);

    /// <summary>
    /// array of the command lists
    /// </summary>
    std::vector<ID3D12GraphicsCommandList*> m_lists;
};

#endif /* D3D12_COMMAND_LIST_BUNDLE_H */
