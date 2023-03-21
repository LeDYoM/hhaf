HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_DEFAULT_SHADER_DATA_INCLUDE_HPP
#define HAF_RESOURCES_DEFAULT_SHADER_DATA_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/resources/types.hpp>
#include <hogl/include/types.hpp>

namespace haf::res
{
using NamedIndexedVertexFormat =
    core::pair<core::str, core::pair<core::u32, VertexFormat>>;
using NamedIndexedVertexFormatContainer =
    core::vector<NamedIndexedVertexFormat>;

struct DefaultAttribs
{
    static void bindDefaultAttributes(ogl::Handle program) noexcept;
    static core::s32 getIndexForName(core::str const& name);
};

struct NamedIndexedVertexFormatFunctions
{
    static core::s32 getIndexForName(NamedIndexedVertexFormatContainer const& container,
                                     core::str const& name);

    static VertexFormat getVertexFormatForIndex(
        NamedIndexedVertexFormatContainer const& container,
        core::u32 const index);

    static VertexFormat getVertexFormatForName(
        NamedIndexedVertexFormatContainer const& container,
        core::str_view const index);

    static bool indexExists(
        NamedIndexedVertexFormatContainer const& container,
        core::u32 const index);
};

}  // namespace haf::res

#endif
