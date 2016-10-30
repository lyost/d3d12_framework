#ifndef STREAMOUTPUTBUFFERDESC_H
#define STREAMOUTPUTBUFFERDESC_H

#include <vector>
#include <d3d11.h>
#include "Graphics/Shaders/Semantics.h"

/// <summary>
/// Describes a stream output buffer
/// </summary>
class StreamOutputBufferDesc
{
  public:
    /// <summary>
    /// Creates a stream output buffer description
    /// </summary>
    /// <param name="stream">
    /// which stream output object in the geometry shader will provide data
    /// </param>
    /// <param name="slot">
    /// which stream output buffer resource slot will receive the data
    /// </param>
    StreamOutputBufferDesc(UINT stream,BYTE slot);
    
    StreamOutputBufferDesc(const StreamOutputBufferDesc& cpy);
    StreamOutputBufferDesc& operator=(const StreamOutputBufferDesc& cpy);
    ~StreamOutputBufferDesc();
    
    /// <summary>
    /// Adds a semantic to the description
    /// </summary>
    /// <param name="size">
    /// number of bytes the sematic will use
    /// </param>
    /// <param name="semantic">
    /// geometry shader output semantic to add
    /// </param>
    /// <param name="index">
    /// index of the semantic
    /// </param>
    /// <param name="start">
    /// start index into multi-component attribues (eg float4) to get data for
    /// </param>
    /// <param name="count">
    /// number of components into multi-component attributes to get data for
    /// <remarks>
    /// The supplied value for size should already take this parameter into
    /// account.  This function will not multiply size by count, it just uses
    /// size as provided.
    /// </remarks>
    /// </param>
    void AddSemantic(UINT size,Semantics semantic,UINT index,BYTE start,
      BYTE count);
    
    /// <summary>
    /// Retreives the stream id
    /// </summary>
    /// <returns>
    /// stream id
    /// </returns>
    UINT GetStream() const;
    
    /// <summary>
    /// Retreives the slot id
    /// </summary>
    /// <returns>
    /// slot id
    /// </returns>
    UINT GetSlot() const;
    
    /// <summary>
    /// Retreives the total size of all added semantics will require
    /// </summary>
    /// <returns>
    /// number of bytes needed to store all semantics
    /// </returns>
    UINT GetStride() const;
    
#ifndef PUBLIC_HEADER
    /// <summary>
    /// Retreives the semantics
    /// </summary>
    /// <returns>
    /// array of semantics
    /// </returns>
    const std::vector<D3D11_SO_DECLARATION_ENTRY>& GetSemantics() const;
#endif /* PUBLIC_HEADER */
    
  private:
    // disabled
    StreamOutputBufferDesc();

    /// <summary>
    /// which stream output object in the geometry shader will provide data
    /// </summary>
    UINT m_stream;
    
    /// <summary>
    /// which stream output buffer resource slot will receive the data
    /// </summary>
    UINT m_slot;
    
    /// <summary>
    /// the semantics
    /// </summary>
    std::vector<D3D11_SO_DECLARATION_ENTRY> m_sems;
    
    /// <summary>
    /// number of bytes that all added semantics take up
    /// </summary>
    UINT m_stride;
};

#endif /* STREAMOUTPUTBUFFERDESC_H */
