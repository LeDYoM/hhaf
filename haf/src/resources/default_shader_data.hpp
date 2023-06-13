HAF_PRAGMA_ONCE
#ifndef HAF_RESOURCES_DEFAULT_SHADER_DATA_INCLUDE_HPP
#define HAF_RESOURCES_DEFAULT_SHADER_DATA_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <hogl/include/types.hpp>

namespace haf::res
{
struct DefaultAttribs
{
    static void bindDefaultAttributes(ogl::Handle program) noexcept;
    static core::s32 getIndexForName(core::str const& name);
};

struct DefaultUniforms
{};

struct DefaultUniformBlocks
{
    static void bindUniformBlock(ogl::Handle program,
                                 core::str const& name,
                                 core::u32 const bindingPoint) noexcept;

    static core::s32 getDefaultUniformBlockBindingPoint(
        core::str_view name) noexcept;
};

}  // namespace haf::res

#endif
