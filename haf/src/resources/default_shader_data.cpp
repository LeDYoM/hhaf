#include "default_shader_data.hpp"
#include <hogl/include/shader_functions.hpp>
#include <hlog/include/hlog.hpp>

using namespace haf::core;

namespace haf::res
{

static NamedIndexedVertexFormatContainer DefaultAttribsTable{
    {"haf_position", {0U, {BufferType::Float, 3U, 1U}}},
    {"haf_color", {1U, {BufferType::Float, 4U, 1U}}},
    {"haf_textureuv", {2U, {BufferType::Float, 2U, 1U}}}};

void DefaultAttribs::bindDefaultAttributes(ogl::Handle program) noexcept
{
    for (auto&& default_attrib : DefaultAttribsTable)
    {
        ogl::bindAttributeIndex(program, default_attrib.second.first,
                                str_view{default_attrib.first.c_str()});
        DisplayLog::debug("DefaultAttribs: Setting default attrib ",
                          default_attrib.first.c_str(), " with index ",
                          default_attrib.second.first);
    }
}

s32 DefaultAttribs::getIndexForName(str const& name)
{
    return NamedIndexedVertexFormatFunctions::getIndexForName(
        DefaultAttribsTable, name);
}

s32 NamedIndexedVertexFormatFunctions::getIndexForName(
    NamedIndexedVertexFormatContainer const& container,
    str const& name)
{
    auto const iterator{
        container.cfind_if([name](NamedIndexedVertexFormat const& element) {
            return name == element.first;
        })};

    return iterator != container.cend()
        ? static_cast<s32>(iterator->second.first)
        : -1;
}

VertexFormat NamedIndexedVertexFormatFunctions::getVertexFormatForIndex(
    NamedIndexedVertexFormatContainer const& container,
    u32 const index)
{
    auto const iterator{
        container.cfind_if([index](NamedIndexedVertexFormat const& element) {
            return index == element.second.first;
        })};

    return iterator != container.cend() ? iterator->second.second
                                        : VertexFormat{};
}

VertexFormat NamedIndexedVertexFormatFunctions::getVertexFormatForName(
    NamedIndexedVertexFormatContainer const& container,
    str_view const name)
{
    auto const iterator{
        container.cfind_if([name](NamedIndexedVertexFormat const& element) {
            return name == element.first;
        })};

    return iterator != container.cend() ? iterator->second.second
                                        : VertexFormat{};
}

bool NamedIndexedVertexFormatFunctions::indexExists(
    NamedIndexedVertexFormatContainer const& container,
    core::u32 const index)
{
    auto const iterator{
        container.cfind_if([index](NamedIndexedVertexFormat const& element) {
            return index == element.second.first;
        })};

    return iterator != container.cend();
}

}  // namespace haf::res
