#include <haf/include/render/buffer_subobject.hpp>

using namespace haf::core;

namespace haf::render
{
BufferSubObject make_bufferSubObject(core::str index,
                                     VertexFormat&& data) noexcept
{
    return BufferSubObject{core::move(index), -1, core::move(data)};
}

BufferSubObject make_bufferSubObject(core::str index,
                                     core::s32 const location,
                                     VertexFormat&& data) noexcept
{
    return BufferSubObject{core::move(index), location, core::move(data)};
}

s32 getIndexForName(BufferSubObjects const& container, str const& name)
{
    auto const iterator{
        container.cfind_if([&name](BufferSubObject const& element) {
            return name == element.index();
        })};

    return iterator != container.cend() ? static_cast<s32>(iterator->location())
                                        : -1;
}

VertexFormat getVertexFormatForIndex(BufferSubObjects const& container,
                                     s32 const index)
{
    auto const iterator{
        container.cfind_if([index](BufferSubObject const& element) {
            return index == element.location();
        })};

    return iterator != container.cend() ? iterator->vertexFormat()
                                        : VertexFormat{};
}

VertexFormat getVertexFormatForName(BufferSubObjects const& container,
                                    str_view const name)
{
    auto const iterator{
        container.cfind_if([name](BufferSubObject const& element) {
            return name == element.index();
        })};

    return iterator != container.cend() ? iterator->vertexFormat()
                                        : VertexFormat{};
}

bool indexExists(BufferSubObjects const& container, s32 const index)
{
    auto const iterator{
        container.cfind_if([index](BufferSubObject const& element) {
            return index == element.location();
        })};

    return iterator != container.cend();
}

}  // namespace haf::render