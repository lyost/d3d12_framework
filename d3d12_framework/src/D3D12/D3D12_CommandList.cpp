#include <sstream>
#include <d3d12.h>
#include "private_inc/D3D12/D3D12_Core.h"
#include "private_inc/D3D12/D3D12_CommandList.h"
#include "private_inc/D3D12/D3D12_Pipeline.h"
#include "private_inc/D3D12/D3D12_RootSignature.h"
#include "private_inc/D3D12/Buffers/D3D12_VertexBufferArray.h"
#include "private_inc/D3D12/Buffers/D3D12_IndexBuffer16.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTarget.h"
#include "private_inc/D3D12/D3D12_HeapArray.h"
#include "private_inc/D3D12/Buffers/D3D12_ConstantBuffer.h"
#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBuffer.h"
#include "private_inc/D3D12/Buffers/D3D12_StreamOutputBufferArray.h"
#include "private_inc/D3D12/Textures/D3D12_Texture1D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2DRenderTarget.h"
#include "private_inc/D3D12/Textures/D3D12_Texture3D.h"
#include "private_inc/D3D12/Textures/D3D12_Texture1DArray.h"
#include "private_inc/D3D12/Textures/D3D12_Texture2DArray.h"
#include "private_inc/D3D12/Textures/D3D12_TextureCube.h"
#include "private_inc/D3D12/Textures/D3D12_TextureCubeArray.h"
#include "private_inc/D3D12/Textures/D3D12_DepthStencil.h"
#include "private_inc/D3D12/Textures/D3D12_RenderTargetMSAA.h"
#include "private_inc/D3D12/Textures/D3D12_DepthStencilMSAA.h"
#include "private_inc/BuildSettings.h"
#include "FrameworkException.h"
using namespace std;

D3D12_CommandList* D3D12_CommandList::Create(const GraphicsCore& graphics, Pipeline* pipeline)
{
  const D3D12_Core&          core           = (const D3D12_Core&)graphics;
  ID3D12Device*              device         = core.GetDevice();
  ID3D12PipelineState*       d3d12_pipeline = pipeline ? ((D3D12_Pipeline*)pipeline)->GetPipeline() : NULL;
  ID3D12CommandAllocator*    command_alloc  = NULL;
  ID3D12GraphicsCommandList* commandList    = NULL;
  HRESULT                    rc;

  rc = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof(ID3D12CommandAllocator), (void**)&command_alloc);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Unable to create command allocator.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }

  rc = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, command_alloc, d3d12_pipeline, __uuidof(ID3D12GraphicsCommandList), (void**)&commandList);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Unable to create command list.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }

  return new D3D12_CommandList(commandList, command_alloc);
}

D3D12_CommandList::D3D12_CommandList(ID3D12GraphicsCommandList* command_list, ID3D12CommandAllocator* allocated_from)
:m_command_list(command_list),
 m_allocated_from(allocated_from)
{
}

D3D12_CommandList::~D3D12_CommandList()
{
  m_allocated_from->Release();
  m_command_list->Release();
}

void D3D12_CommandList::Reset(Pipeline* pipeline)
{
  ID3D12PipelineState* d3d12_pipeline = pipeline ? ((D3D12_Pipeline*)pipeline)->GetPipeline() : NULL;

  HRESULT rc = m_allocated_from->Reset();
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Unable to reset command allocator.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }
  rc = m_command_list->Reset(m_allocated_from, d3d12_pipeline);
  if (FAILED(rc))
  {
    ostringstream out;
    out << "Unable to reset command list.  HRESULT: " << rc;
    throw FrameworkException(out.str());
  }
}

void D3D12_CommandList::Close()
{
  HRESULT rc = m_command_list->Close();

  if (FAILED(rc))
  {
    ostringstream out;
    out << "Failed to close command list.  HRESULT = " << rc;
    throw FrameworkException(out.str());
  }
}

void D3D12_CommandList::SetRootSignature(const RootSignature& sig)
{
  const D3D12_RootSignature& root_sig = (const D3D12_RootSignature&)sig;
  m_command_list->SetGraphicsRootSignature(root_sig.GetRootSignature());
}

void D3D12_CommandList::SetHeapArray(const HeapArray& heap_array)
{
  const D3D12_HeapArray& d3d12_heap_array = (const D3D12_HeapArray&)heap_array;
  m_command_list->SetDescriptorHeaps(d3d12_heap_array.GetLength(), d3d12_heap_array.GetArray());
}

void D3D12_CommandList::SetConstantBuffer(UINT slot, const ConstantBuffer& constant_buffer)
{
  const D3D12_ConstantBuffer& buffer = (const D3D12_ConstantBuffer&)constant_buffer;
  m_command_list->SetGraphicsRootConstantBufferView(slot, buffer.GetGPUAddr());
}

void D3D12_CommandList::SetTextureAsStartOfDescriptorTable(UINT slot, const Texture1D& texture)
{
  const D3D12_Texture1D& tex = (const D3D12_Texture1D&)texture;
  m_command_list->SetGraphicsRootDescriptorTable(slot, tex.GetGPUAddr());
}

void D3D12_CommandList::SetTextureAsStartOfDescriptorTable(UINT slot, const Texture2D& texture)
{
  const D3D12_Texture2D& tex = (const D3D12_Texture2D&)texture;
  m_command_list->SetGraphicsRootDescriptorTable(slot, tex.GetGPUAddr());
}

void D3D12_CommandList::SetTextureAsStartOfDescriptorTable(UINT slot, const Texture2DRenderTarget& texture)
{
  const D3D12_Texture2DRenderTarget& tex = (const D3D12_Texture2DRenderTarget&)texture;
  m_command_list->SetGraphicsRootDescriptorTable(slot, tex.GetGPUAddr());
}

void D3D12_CommandList::SetTextureAsStartOfDescriptorTable(UINT slot, const Texture3D& texture)
{
  const D3D12_Texture3D& tex = (const D3D12_Texture3D&)texture;
  m_command_list->SetGraphicsRootDescriptorTable(slot, tex.GetGPUAddr());
}

void D3D12_CommandList::SetTextureAsStartOfDescriptorTable(UINT slot, const Texture1DArray& texture)
{
  const D3D12_Texture1DArray& tex = (const D3D12_Texture1DArray&)texture;
  m_command_list->SetGraphicsRootDescriptorTable(slot, tex.GetGPUAddr());
}

void D3D12_CommandList::SetTextureAsStartOfDescriptorTable(UINT slot, const Texture2DArray& texture)
{
  const D3D12_Texture2DArray& tex = (const D3D12_Texture2DArray&)texture;
  m_command_list->SetGraphicsRootDescriptorTable(slot, tex.GetGPUAddr());
}

void D3D12_CommandList::SetTextureAsStartOfDescriptorTable(UINT slot, const TextureCube& texture)
{
  const D3D12_TextureCube& tex = (const D3D12_TextureCube&)texture;
  m_command_list->SetGraphicsRootDescriptorTable(slot, tex.GetGPUAddr());
}

void D3D12_CommandList::SetTextureAsStartOfDescriptorTable(UINT slot, const TextureCubeArray& texture)
{
  const D3D12_TextureCubeArray& tex = (const D3D12_TextureCubeArray&)texture;
  m_command_list->SetGraphicsRootDescriptorTable(slot, tex.GetGPUAddr());
}

void D3D12_CommandList::IASetTopology(IATopology topology)
{
  m_command_list->IASetPrimitiveTopology((D3D_PRIMITIVE_TOPOLOGY)topology);
}

void D3D12_CommandList::IASetVertexBuffers(const VertexBufferArray& buffers)
{
  const D3D12_VertexBufferArray&  buffer_array = (const D3D12_VertexBufferArray&)buffers;
  const D3D12_VERTEX_BUFFER_VIEW* raw_array    = buffer_array.GetArray();
  UINT num_buffers = buffer_array.GetNumBuffers();

#ifdef VALIDATE_FUNCTION_ARGUMENTS
  for (UINT i = 0; i < num_buffers; i++)
  {
    if (raw_array[i].BufferLocation == 0 && raw_array[i].SizeInBytes == 0)
    {
      throw FrameworkException("Entry in vertex array unset");
    }
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_command_list->IASetVertexBuffers(0, num_buffers, raw_array);
}

void D3D12_CommandList::IASetIndexBuffer(const IndexBuffer& buffer)
{
  const D3D12_INDEX_BUFFER_VIEW& index_buffer = ((const D3D12_IndexBuffer16&)buffer).GetBuffer();
  m_command_list->IASetIndexBuffer(&index_buffer);
}

void D3D12_CommandList::SOSetBuffers(const StreamOutputBufferArray& buffers)
{
  const D3D12_StreamOutputBufferArray& buffer_array = (const D3D12_StreamOutputBufferArray&)buffers;
  m_command_list->SOSetTargets(0, buffer_array.GetNumBuffers(), buffer_array.GetArray());
}

void D3D12_CommandList::SOBufferToVertexBuffer(const StreamOutputBuffer& buffer)
{
  const D3D12_StreamOutputBuffer& so_buffer = (const D3D12_StreamOutputBuffer&)buffer;
  D3D12_RESOURCE_BARRIER barrier;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource   = so_buffer.GetResource();
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_STREAM_OUT;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_GENERIC_READ;
  m_command_list->ResourceBarrier(1, &barrier);
}

void D3D12_CommandList::SOVertexBufferToStreamOutputBuffer(const StreamOutputBuffer& buffer)
{
  const D3D12_StreamOutputBuffer& so_buffer = (const D3D12_StreamOutputBuffer&)buffer;
  D3D12_RESOURCE_BARRIER barrier;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource   = so_buffer.GetResource();
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_STREAM_OUT;
  m_command_list->ResourceBarrier(1, &barrier);
}

void D3D12_CommandList::RSSetViewport(const Viewport& viewport)
{
  m_command_list->RSSetViewports(1, (const D3D12_VIEWPORT*)&viewport);
}

void D3D12_CommandList::RSSetViewports(const Viewports& viewports)
{
  const D3D12_VIEWPORT* viewport_array = (const D3D12_VIEWPORT*)viewports.GetViewports();
  m_command_list->RSSetViewports(viewports.GetNumInUse(), viewport_array);
}

void D3D12_CommandList::RSSetViewports(const Viewports& viewports, UINT start, UINT num)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if ((start + num) >= Viewports::GetMaxViewports())
  {
    throw FrameworkException("Requested start index and number of viewports is beyond the length of the array stored in a Viewports instance");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  const D3D12_VIEWPORT* viewport_array = (const D3D12_VIEWPORT*)viewports.GetViewports();
  m_command_list->RSSetViewports(num, viewport_array + start);
}

void D3D12_CommandList::RSSetScissorRect(const RECT& rect)
{
  m_command_list->RSSetScissorRects(1, &rect);
}

void D3D12_CommandList::RSSetScissorRects(const vector<RECT>& rects)
{
  UINT num_rects = (UINT)rects.size();
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if (num_rects != rects.size())
  {
    throw FrameworkException("Trying to set too many scissor rects");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */
  m_command_list->RSSetScissorRects(num_rects, &rects[0]);
}

void D3D12_CommandList::RSSetScissorRects(const vector<RECT>& rects, UINT start, UINT num)
{
#ifdef VALIDATE_FUNCTION_ARGUMENTS
  if ((start + num) >= rects.size())
  {
    throw FrameworkException("Requested start index and number of elements is beyond the length of the array");
  }
#endif /* VALIDATE_FUNCTION_ARGUMENTS */

  m_command_list->RSSetScissorRects(num, &rects[start]);
}

void D3D12_CommandList::PrepRenderTarget(const RenderTarget& target)
{
  D3D12_RESOURCE_BARRIER barrier;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource   = ((const D3D12_RenderTarget&)target).GetResource();
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_RENDER_TARGET;
  m_command_list->ResourceBarrier(1, &barrier);
}

void D3D12_CommandList::PrepRenderTarget(const RenderTargetMSAA& target)
{
  D3D12_RESOURCE_BARRIER barrier;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource   = ((const D3D12_RenderTargetMSAA&)target).GetResource();
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_RENDER_TARGET;
  m_command_list->ResourceBarrier(1, &barrier);
}

void D3D12_CommandList::RenderTargetToPresent(const RenderTarget& target)
{
  D3D12_RESOURCE_BARRIER barrier;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource   = ((const D3D12_RenderTarget&)target).GetResource();
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;
  m_command_list->ResourceBarrier(1, &barrier);
}

void D3D12_CommandList::RenderTargetResolvedToPresent(const RenderTarget& target)
{
  D3D12_RESOURCE_BARRIER barrier;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource   = ((const D3D12_RenderTarget&)target).GetResource();
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RESOLVE_DEST;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_PRESENT;
  m_command_list->ResourceBarrier(1, &barrier);
}

void D3D12_CommandList::RenderTargetToResolved(const RenderTargetMSAA& src, const RenderTarget& dst)
{
  ID3D12Resource* src_resource = ((const D3D12_RenderTargetMSAA&)src).GetResource();
  ID3D12Resource* dst_resource = ((const D3D12_RenderTarget&)dst).GetResource();

  D3D12_RESOURCE_BARRIER barrier[2];
  barrier[0].Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier[0].Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier[0].Transition.pResource   = src_resource;
  barrier[0].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier[0].Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
  barrier[0].Transition.StateAfter  = D3D12_RESOURCE_STATE_RESOLVE_SOURCE;

  barrier[1].Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier[1].Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier[1].Transition.pResource   = dst_resource;
  barrier[1].Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier[1].Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
  barrier[1].Transition.StateAfter  = D3D12_RESOURCE_STATE_RESOLVE_DEST;

  m_command_list->ResourceBarrier(2, barrier);
  m_command_list->ResolveSubresource(dst_resource, 0, src_resource, 0, dst_resource->GetDesc().Format);
}

void D3D12_CommandList::TextureToRenderTarget(const Texture2DRenderTarget& texture)
{
  D3D12_RESOURCE_BARRIER barrier;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource   = ((const D3D12_Texture2DRenderTarget&)texture).GetResource();
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_GENERIC_READ;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_RENDER_TARGET;
  m_command_list->ResourceBarrier(1, &barrier);
}

void D3D12_CommandList::RenderTargetToTexture(const RenderTarget& target)
{
  D3D12_RESOURCE_BARRIER barrier;
  barrier.Type                   = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
  barrier.Flags                  = D3D12_RESOURCE_BARRIER_FLAG_NONE;
  barrier.Transition.pResource   = ((const D3D12_RenderTarget&)target).GetResource();
  barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
  barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
  barrier.Transition.StateAfter  = D3D12_RESOURCE_STATE_GENERIC_READ;
  m_command_list->ResourceBarrier(1, &barrier);
}

void D3D12_CommandList::ClearRenderTarget(const RenderTarget& target, const float clear_color[4])
{
  const D3D12_RenderTarget& render_target = (const D3D12_RenderTarget&)target;
  m_command_list->ClearRenderTargetView(render_target.GetHandle(), clear_color, 0, NULL);
}

void D3D12_CommandList::ClearRenderTarget(const RenderTargetMSAA& target, const float clear_color[4])
{
  const D3D12_RenderTargetMSAA& render_target = (const D3D12_RenderTargetMSAA&)target;
  m_command_list->ClearRenderTargetView(render_target.GetHandle(), clear_color, 0, NULL);
}

void D3D12_CommandList::ClearDepthStencil(const DepthStencil& depth_stencil, float depth_clear_value)
{
  const D3D12_DepthStencil& depth = (const D3D12_DepthStencil&)depth_stencil;
  m_command_list->ClearDepthStencilView(depth.GetHandle(), D3D12_CLEAR_FLAG_DEPTH, depth_clear_value, 0, 0, NULL);
}

void D3D12_CommandList::ClearDepthStencil(const DepthStencilMSAA& depth_stencil, float depth_clear_value)
{
  const D3D12_DepthStencilMSAA& depth = (const D3D12_DepthStencilMSAA&)depth_stencil;
  m_command_list->ClearDepthStencilView(depth.GetHandle(), D3D12_CLEAR_FLAG_DEPTH, depth_clear_value, 0, 0, NULL);
}

void D3D12_CommandList::OMSetRenderTarget(const RenderTarget& target)
{
  const D3D12_RenderTarget& render_target = (const D3D12_RenderTarget&)target;
  const D3D12_CPU_DESCRIPTOR_HANDLE& handle = render_target.GetHandle();
  m_command_list->OMSetRenderTargets(1, &handle, false, NULL);
}

void D3D12_CommandList::OMSetRenderTarget(const RenderTarget& target, const DepthStencil& depth_stencil)
{
  const D3D12_RenderTarget& render_target = (const D3D12_RenderTarget&)target;
  const D3D12_CPU_DESCRIPTOR_HANDLE& handle = render_target.GetHandle();
  const D3D12_DepthStencil& depth = (const D3D12_DepthStencil&)depth_stencil;
  const D3D12_CPU_DESCRIPTOR_HANDLE& depth_handle = depth.GetHandle();
  m_command_list->OMSetRenderTargets(1, &handle, false, &depth_handle);
}

void D3D12_CommandList::OMSetRenderTarget(const RenderTargetMSAA& target, const DepthStencilMSAA& depth_stencil)
{
  const D3D12_RenderTargetMSAA& render_target = (const D3D12_RenderTargetMSAA&)target;
  const D3D12_CPU_DESCRIPTOR_HANDLE& handle = render_target.GetHandle();
  const D3D12_DepthStencilMSAA& depth = (const D3D12_DepthStencilMSAA&)depth_stencil;
  const D3D12_CPU_DESCRIPTOR_HANDLE& depth_handle = depth.GetHandle();
  m_command_list->OMSetRenderTargets(1, &handle, false, &depth_handle);
}

void D3D12_CommandList::DrawIndexedInstanced(UINT indices_per_instance, UINT instance_cnt, UINT start_index)
{
  m_command_list->DrawIndexedInstanced(indices_per_instance, instance_cnt, start_index, 0, 0);
}

void D3D12_CommandList::DrawInstanced(UINT vertices_per_instance, UINT instance_cnt, UINT start_index)
{
  m_command_list->DrawInstanced(vertices_per_instance, instance_cnt, start_index, 0);
}

ID3D12GraphicsCommandList* D3D12_CommandList::GetCommandList() const
{
  return m_command_list;
}
