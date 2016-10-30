#ifndef INDEX_BUFFER16_H
#define INDEX_BUFFER16_H

#include "Graphics/GraphicsCore.h"
#include "Graphics/Buffers/IndexBuffer.h"

/// <summary>
/// Index buffer for 16bit long entries
/// </summary>
class IndexBuffer16 : public IndexBuffer
{
  public:
    /// <summary>
    /// Creates an index buffer
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="num">
    /// number of entries in the buffer
    /// </param>
    /// <param name="data">
    /// initial data for the index buffer
    /// </param>
    /// <returns>
    /// pointer to the index buffer instance on success
    /// NULL on error
    /// </returns>
    static IndexBuffer16* CreateD3D12(GraphicsCore& graphics, UINT num, const WORD* data);
    
    /// <summary>
    /// Cleans up the index buffer
    /// </summary>
    virtual ~IndexBuffer16();
    
  protected:
    IndexBuffer16();
    
  private:
    // disabled
    IndexBuffer16(const IndexBuffer16& cpy);
    IndexBuffer16& operator=(const IndexBuffer16& cpy);
};

#endif /* INDEX+BUFFER16_H */
