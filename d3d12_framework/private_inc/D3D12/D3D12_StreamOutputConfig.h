#ifndef D3D12_STREAM_OUTPUT_CONFIG_H
#define D3D12_STREAM_OUTPUT_CONFIG_H

#include <d3d12.h>
#include "Graphics/StreamOutputConfig.h"

class D3D12_StreamOutputConfig : public StreamOutputConfig
{
  public:
    D3D12_StreamOutputConfig(UINT num_entries);

    ~D3D12_StreamOutputConfig();

    /// <summary>
    /// Sets the index number of the stream to send to the rasterizer stage
    /// </summary>
    /// <param name="index">
    /// index of the stream to send to the rasterizer stage
    /// </param>
    void SetStreamToRasterizer(UINT index);

    /// <summary>
    /// Sets the configuration for an entry
    /// </summary>
    /// <param name="entry_index">
    /// index of the entry to set
    /// </param>
    /// <param name="stream_index">
    /// index of the stream this entry applies to
    /// </param>
    /// <param name="sem">
    /// semantic of this entry
    /// </param>
    /// <param name="sem_index">
    /// semantic's index
    /// </param>
    /// <param name="start_component">
    /// starting index of the component to include in stream output (0 = x, 1 = y, 2 = z, 3 = w)
    /// </param>
    /// <param name="num_components">
    /// number of components to include in the stream output
    /// </param>
    /// <param name="output_slot">
    /// index of the stream output buffer to use
    /// </param>
    /// <param name="stride">
    /// number of bytes in this entry
    /// </param>
    void SetEntry(UINT entry_index, UINT stream_index, Semantics sem, UINT sem_index, BYTE start_component, BYTE num_components, BYTE output_slot, UINT stride);

    /// <summary>
    /// Retrieves the stream output description
    /// </summary>
    /// <returns>
    /// stream output description
    /// </returns>
    const D3D12_STREAM_OUTPUT_DESC& GetDesc() const;

  private:
    // disabled
    D3D12_StreamOutputConfig();
    D3D12_StreamOutputConfig(const D3D12_StreamOutputConfig& cpy);
    D3D12_StreamOutputConfig& operator=(const D3D12_StreamOutputConfig& cpy);

    /// <summary>
    /// stream output description
    /// </summary>
    D3D12_STREAM_OUTPUT_DESC m_desc;

    /// <summary>
    /// array of stream output entry descriptions
    /// </summary>
    /// <remarks>
    /// since pSODeclaration in m_desc is declared const, keeping a pointer to a mutable version of the same memory
    /// </remarks>
    D3D12_SO_DECLARATION_ENTRY* m_entries;

    /// <summary>
    /// array of buffer strides
    /// </summary>
    /// <remarks>
    /// since pBufferStrides in m_desc is declared const, keeping a pointer to a mutable version of the same memory
    /// </remarks>
    UINT* m_strides;

    /// <summary>
    /// number of entries in the config
    /// </summary>
    UINT m_num_entries;
};

#endif /* D3D12_STREAM_OUTPUT_CONFIG_H */
