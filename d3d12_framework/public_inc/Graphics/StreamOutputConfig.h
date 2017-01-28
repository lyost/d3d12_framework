#ifndef STREAM_OUTPUT_CONFIG_H
#define STREAM_OUTPUT_CONFIG_H

#include <windows.h>
#include "Semantics.h"

class StreamOutputConfig
{
  public:
    /// <summary>
    /// Creates a blank StreamOutputConfig with the specified number of entries
    /// </summary>
    /// <param name="num_entries">
    /// number of entries in the config
    /// </param>
    /// <returns>
    /// pointer to the stream output config instance on success
    /// NULL on error
    /// </returns>
    static StreamOutputConfig* CreateD3D12(UINT num_entries);

    virtual ~StreamOutputConfig();

    /// <summary>
    /// Sets the index number of the stream to send to the rasterizer stage
    /// </summary>
    /// <param name="index">
    /// index of the stream to send to the rasterizer stage
    /// </param>
    virtual void SetStreamToRasterizer(UINT index) = 0;

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
    virtual void SetEntry(UINT entry_index, UINT stream_index, Semantics sem, UINT sem_index, BYTE start_component, BYTE num_components, BYTE output_slot, UINT stride) = 0;

  protected:
    StreamOutputConfig();

  private:
    // disabled
    StreamOutputConfig(const StreamOutputConfig& cpy);
    StreamOutputConfig& operator=(const StreamOutputConfig& cpy);
};

#endif /* STREAM_OUTPUT_CONFIG_H */
