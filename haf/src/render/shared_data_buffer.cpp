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

bool SharedDataBuffer::setBindingPoint(u32 const bindingPoint)
{
    ogl::bindBufferUniformBlock(bindingPoint, m_buffer_object_unsized.handle());
    return true;
}

bool SharedDataBuffer::autoBindToDefault()
{
    for (auto const& bufferSubObject : m_buffer_object_unsized.subObjects())
    {
        auto const index{
            res::DefaultUniformBlocks::getDefaultUniformBlockBindingPoint(
                bufferSubObject.index().to_view())};
        if (index > -1)
        {
            DisplayLog::debug(StaticTypeName,
                              ": Binding default uniform group location: ",
                              bufferSubObject.index(), "with location ", index);
            setBindingPoint(static_cast<u32>(index));
        }
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

u32 SharedDataBuffer::sizeOfStruct() const noexcept
{
    return m_buffer_object_unsized.sizeOfStruct();
}

BufferSubObjects const& SharedDataBuffer::subObjects() const noexcept
{
    return m_buffer_object_unsized.subObjects();
}

void* SharedDataBuffer::lockForWrite(core::u32 const size)
{
    return m_buffer_object_unsized.lock(size);
}

void SharedDataBuffer::unlock()
{
    m_buffer_object_unsized.unlock();
}

}  // namespace haf::render
