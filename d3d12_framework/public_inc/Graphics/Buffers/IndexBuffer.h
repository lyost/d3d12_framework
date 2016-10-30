#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <windows.h>

/// <summary>
/// Base class for index buffers
/// </summary>
class IndexBuffer
{
  public:
    virtual ~IndexBuffer();

    /// <summary>
    /// Retrieves the number of indices in the buffer
    /// </summary>
    /// <returns>
    /// number of indices
    /// </returns>
    virtual UINT GetNumIndices() const = 0;
    
  protected:
    IndexBuffer();
    
  private:
    // disabled
    IndexBuffer(const IndexBuffer& cpy);
    IndexBuffer& operator=(const IndexBuffer& cpy);
};

#endif /* INDEX_BUFFER_H */
