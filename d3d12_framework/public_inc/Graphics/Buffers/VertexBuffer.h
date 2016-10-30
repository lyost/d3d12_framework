#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBufferArray;

#include <windows.h>

/// <summary>
/// Base class for vertex buffers
/// </summary>
class VertexBuffer
{
  public:
    virtual ~VertexBuffer();

    /// <summary>
    /// Retrieves the number of entries in the buffer
    /// </summary>
    /// <returns>
    /// number of entries
    /// </returns>
    virtual UINT GetNumVertices() const = 0;
    
  protected:
    VertexBuffer();
    
  private:
    // disabled
    VertexBuffer(const VertexBuffer& cpy);
    VertexBuffer& operator=(const VertexBuffer& cpy);
};

#endif /* VERTEX_BUFFER_H */
