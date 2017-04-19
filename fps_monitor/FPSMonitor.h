#ifndef FPS_MONITOR_H
#define FPS_MONITOR_H

#include <map>
#include <vector>
#include <directxmath.h>
#include "Graphics/Textures/Texture2D.h"
#include "Graphics/Buffers/ConstantBuffer.h"
#include "Graphics/Buffers/IndexBuffer16.h"

class FPSMonitor
{
  public:
    /// <summary>
    /// Creates a monitor using the specified font information
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    /// <param name="sample_size">
    /// number of samples to use when computing the FPS
    /// </param>
    /// <param name="lookup_table">
    /// map of characters to their uv coordinates in the order of left, right, top, bottom
    /// </param>
    /// <param name="width">
    /// width of the font's texture in pixels
    /// </param>
    /// <param name="height">
    /// height of the font's texture in pixels
    /// </param>
    /// <param name="bytes">
    /// raw pixels of the image to use as the font
    /// </param>
    /// <param name="char_width">
    /// width of a character in pixels
    /// </param>
    /// <param name="char_height">
    /// height of a character in pixels
    /// </param>
    FPSMonitor(GraphicsCore& graphics, UINT sample_size, const std::map<char, std::vector<float> >& lookup_table, UINT width, UINT height, const std::vector<UINT8>& bytes, UINT char_width,
      UINT char_height);

    ~FPSMonitor();

    /// <summary>
    /// Informs the FPS meter that another frame update has occured
    /// </summary>
    /// <param name="ms">
    /// number of milliseconds since the last frame update
    /// </param>
    void Update(UINT ms);

    /// <summary>
    /// Draws the FPS monitor
    /// </summary>
    /// <param name="command_list">
    /// command list to use for drawing
    /// </param>
    void Draw(GraphicsCore& graphics, CommandList* command_list) const;

    /// <summary>
    /// Informs the monitor the core graphics interface has processed a resize event
    /// </summary>
    /// <param name="graphics">
    /// core graphics interface
    /// </param>
    void Resize(GraphicsCore& graphics);

  private:
    // disabled
    FPSMonitor();
    FPSMonitor(const FPSMonitor& cpy);
    FPSMonitor& operator=(const FPSMonitor& cpy);

    enum
    {
      VERTS_PER_CHAR   = 4,
      INDICES_PER_CHAR = 6,
      CHARS_PER_ROW    = 9,
      NUM_ROWS         = 3,
    };

    struct VertexBufferEntry
    {
      DirectX::XMFLOAT2 pos;
      DirectX::XMFLOAT2 uv;
      UINT              lookup_index;
    };

    /// <summary>
    /// data for the instance buffer
    /// </summary>
    VertexBufferEntry m_vertex_buffer_data[VERTS_PER_CHAR * CHARS_PER_ROW * NUM_ROWS];

    /// <summary>
    /// FPS samples
    /// </summary>
    std::vector<UINT> m_samples;

    /// <summary>
    /// index into m_samples for the next FPS sample data
    /// </summary>
    UINT m_next_sample_index;

    /// <summary>
    /// Maps the characters to their corresponding index in the lookup table
    /// </summary>
    std::map<char, UINT> m_key_to_index;

    /// <summary>
    /// width of the display of the characters in clip space
    /// </summary>
    float m_char_width;

    /// <summary>
    /// height of the display of the characters in clip space
    /// </summary>
    float m_char_height;

    /// <summary>
    /// width of a character in pixels
    /// </summary>
    UINT m_char_width_px;

    /// <summary>
    /// height of a character in pixels
    /// </summary>
    UINT m_char_height_px;

    /// <summary>
    /// texture containing the font
    /// </summary>
    Texture2D* m_font;

    /// <summary>
    /// lookup table for the uv coordinates of the various characters in the m_font texture
    /// </summary>
    ConstantBuffer* m_lookup_table;

    /// <summary>
    /// root signatures for the test case
    /// </summary>
    RootSignature* m_root_sig;

    /// <summary>
    /// graphics pipeline
    /// </summary>
    Pipeline* m_pipeline;

    /// <summary>
    /// corresponding scissor rect for the default viewport
    /// </summary>
    RECT m_scissor_rect;

    /// <summary>
    /// vertex buffer array for supplying the vertex buffer to the rendering process
    /// </summary>
    VertexBufferArray* m_vert_array;

    /// <summary>
    /// vertex buffer for displaying the FPS values
    /// </summary>
    VertexBuffer_Custom* m_verts;

    /// <summary>
    /// index buffer for displaying the FPS values
    /// </summary>
    IndexBuffer16* m_indices;

    /// <summary>
    /// Descriptor Heap for allocating the buffers from
    /// </summary>
    ShaderResourceDescHeap* m_shader_buffer_heap;

    /// <summary>
    /// array of descriptor heaps
    /// </summary>
    HeapArray* m_heap_array;
};

#endif /* FPS_MONITOR_H */
