#ifndef STREAMOUTPUTBUFFER_H
#define STREAMOUTPUTBUFFER_H

#include "Graphics/D3D11_Core.h"
#include "StreamOutputBufferDesc.h"

/// <summary>
/// Buffer for a single stream output from the geometry shader stage
/// </summary>
/// <remarks>
/// To write to the StreamOutputBuffer, supply it to a geometry shader and have
/// it do the writing.  To use the results of previous writes for rendering,
/// use MakeActive to supply the data to input assembler stage and use
/// D3D11_Core::DrawAuto (todo) on the same device context
/// </remarks>
class StreamOutputBuffer
{
  public:
    /// <summary>
    /// Creates a stream output buffer based on the specified description that
    /// can hold the specified number of elements
    /// </summary>
    /// <param name="graphics">
    /// D3D11 instance to create the buffer for
    /// </param>
    /// <param name="desc">
    /// description of the stream output buffer to create
    /// </param>
    /// <param name="num">
    /// number of elements that the buffer should be able to hold
    /// </param>
    static StreamOutputBuffer* Create(D3D11_Core& graphics,
      const StreamOutputBufferDesc& desc,UINT num);
    
    virtual ~StreamOutputBuffer();
    
    /// <summary>
    /// Setup the stream output buffer as input to the input assembler stage.
    /// <remarks>
    /// The vertex shader used for rendering needs to have an input layout that
    /// is compatible with the format of the stream output.
    /// </remarks>
    /// <summary>
    /// <param name="context">
    /// D3D11 context to apply the buffer to
    /// </param>
    void MakeActive(ID3D11DeviceContext* context);
    
    /// <summary>
    /// Retreives the number of entries in the buffer
    /// <summary>
    /// <returns>
    /// number of entries in the buffer
    /// </returns>
    UINT GetNumEntries() const;
    
    /// <summary>
    /// Retrieves the number of bytes in an element
    /// </summary>
    /// <returns>
    /// number of bytes between each element in the vertex buffer
    /// </returns>
    UINT GetStride() const;
    
    /// <summary>
    /// Retreives the stream output buffer resource slot index
    /// </summary>
    /// <returns>
    /// slot index
    /// </returns>
    UINT GetSlot() const;

#ifndef PUBLIC_HEADER
    /// <summary>
    /// Retreives the buffer
    /// </summary>
    /// <returns>
    /// D3D11 buffer
    /// </returns>
    ID3D11Buffer* GetBuffer() const;
#endif /* PUBLIC_HEADER */
    
  protected:
    /// <summary>
    /// Creates a stream output buffer
    /// </summary>
    /// <param name="buffer">
    /// D3D11 stream output buffer
    /// </param>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <param name="stride">
    /// number of bytes in each entry
    /// </param>
    /// <param name="slot">
    /// which output buffer slot to use
    /// </param>
    StreamOutputBuffer(ID3D11Buffer* buffer,UINT num,UINT stride,UINT slot);
    
    /// <summary>
    /// Creates a stream output buffer
    /// </summary>
    /// <param name="graphics">
    /// D3D11 instance to create the vertex buffer for
    /// </param>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <param name="size">
    /// number of bytes in 1 entry
    /// </param>
    /// <param name="host">
    /// true if the buffer is for copying data to the host
    /// false if the data will stay on the GPU
    /// </param>
    /// <returns>
    /// D3D11 stream output buffer
    /// NULL on error
    /// </returns>
    static ID3D11Buffer* CreateBuffer(D3D11_Core& graphics,UINT num,UINT size,
      bool host);
    
    /// <summary>
    /// D3D11 buffer for the data
    /// </summary>
    ID3D11Buffer* m_buffer;
    
  private:
    // disabled
    StreamOutputBuffer();
    StreamOutputBuffer(const StreamOutputBuffer& cpy);
    StreamOutputBuffer& operator=(const StreamOutputBuffer& cpy);
    
    /// <summary>
    /// number of bytes in an entry
    /// </summary>
    UINT m_stride;
    
    /// <summary>
    /// number of entries
    /// </summary>
    UINT m_num;

    /// <summary>
    /// stream output buffer resource slot the instance uses when bound to the
    /// pipeline
    /// </summary>
    UINT m_slot;
};

#endif /* STREAMOUTPUTBUFFER_H */
