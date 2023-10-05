#include <haf/include/render/shared_data_buffer.hpp>
#include <haf/include/render/render_buffer.hpp>
#include <hogl/include/types.hpp>
#include <hogl/include/buffer_functions.hpp>
#include <hlog/include/hlog.hpp>
#include "resources/default_shader_data.hpp"

using namespace haf::core;

namespace haf::render
{
SharedDataBuffer::SharedDataBuffer(
    BufferObjectUnsizedConstructParams&& bufferObjectUnsizedConstructParams) :
    m_buffer_object_unsized{core::move(bufferObjectUnsizedConstructParams)}
{}

SharedDataBuffer::~SharedDataBuffer() = default;

void SharedDataBuffer::setBindingPoint(u32 const bindingPoint)
{
    m_bindingPoint = bindingPoint;
}

bool SharedDataBuffer::autoBindToDefault()
{
    auto const index{
        res::DefaultUniformBlocks::getDefaultUniformBlockBindingPoint(
            m_buffer_object_unsized.subObject().index().to_view())};
    if (index > -1)
    {
        logger::DisplayLog::debug(StaticTypeName,
                          ": Binding default uniform group location: ",
                          m_buffer_object_unsized.subObject().index(),
                          "with location ", index);
        setBindingPoint(static_cast<u32>(index));
    }
    return true;
}

bool SharedDataBuffer::isValid() const
{
    return m_buffer_object_unsized.isValid();
}

u32 SharedDataBuffer::handle() const noexcept
{
    return m_buffer_object_unsized.handle();
}

u32 SharedDataBuffer::vertexFormatSize() const noexcept
{
    return m_buffer_object_unsized.vertexFormatSize();
}

BufferSubObject const& SharedDataBuffer::subObject() const noexcept
{
    return m_buffer_object_unsized.subObject();
}

void* SharedDataBuffer::lockForWrite(core::u32 const size)
{
    return m_buffer_object_unsized.lock(size);
}

void SharedDataBuffer::unlock()
{
    m_buffer_object_unsized.unlock();
}

void SharedDataBuffer::bindSharedBuffer()
{
    ogl::bindBufferUniformBlock(m_bindingPoint,
                                m_buffer_object_unsized.handle());
}

}  // namespace haf::render
