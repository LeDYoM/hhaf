#include <haf/include/render/buffer_object.hpp>
#include <haf/include/render/render_buffer.hpp>
#include <hogl/include/types.hpp>
#include <hogl/include/buffer_functions.hpp>

using namespace haf::core;

namespace haf::render
{
BufferObject::BufferObject(
    BufferObjectConstructParams&& bufferObjectConstructParams) :
    m_bufferObjectUnsized{core::move(bufferObjectConstructParams)},
    m_size{core::move(bufferObjectConstructParams.size)}
{}

BufferObject::~BufferObject() = default;

bool BufferObject::isValid() const
{
    return m_bufferObjectUnsized.isValid();
}

u32 BufferObject::handle() const noexcept
{
    return m_bufferObjectUnsized.handle();
}

u32 BufferObject::sizeOfStruct() const noexcept
{
    return m_bufferObjectUnsized.sizeOfStruct();
}

BufferSubObjects const& BufferObject::subObjects() const noexcept
{
    return m_bufferObjectUnsized.subObjects();
}

u32 BufferObject::size() const noexcept
{
    return m_size;
}

}  // namespace haf::render
