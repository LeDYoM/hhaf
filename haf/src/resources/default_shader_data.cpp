#include "default_shader_data.hpp"
#include <haf/include/core/matrix4x4.hpp>
#include <haf/include/render/buffer_subobject.hpp>
#include <haf/include/render/vertex_formats.hpp>

#include <hogl/include/shader_functions.hpp>
#include <hlog/include/hlog.hpp>

using namespace haf::core;
using namespace haf::render;

namespace haf::res
{
namespace
{
static render::BufferSubObjects DefaultAttribsTable{
    {"haf_position", 0U, getVertexFormat<vector3df>()},
    {"haf_color", 1U, getVertexFormat<vector3df>()},
    {"haf_textureuv", 2U, getVertexFormat<vector2df>()}};

static render::BufferSubObjects DefaultUniformBlocks{
    {"HAFCameraData", 0U, getVertexFormat<math::Matrix4x4>()}};

using UniformBlocksBindingType  = pair<str, u32>;
using UniformBlocksBindingsType = vector<UniformBlocksBindingType>;

static UniformBlocksBindingsType DefaultUniformBlocksBindings{
    {"HAFCameraData", 1U}};

}  // namespace

void DefaultAttribs::bindDefaultAttributes(ogl::Handle program) noexcept
{
    for (auto&& default_attrib : DefaultAttribsTable)
    {
        ogl::bindAttributeIndex(program, default_attrib.location(),
                                str_view{default_attrib.index().c_str()});
        DisplayLog::debug("DefaultAttribs: Setting default attrib ",
                          default_attrib.index().c_str(), " with index ",
                          default_attrib.location());
    }
}

s32 DefaultAttribs::getIndexForName(str const& name)
{
    return render::getIndexForName(DefaultAttribsTable, name);
}

void DefaultUniformBlocks::bindUniformBlock(
    ogl::Handle /*program*/,
    core::str const& /*name*/,
    core::u32 const /*bindingPoint*/) noexcept
{}

core::s32 DefaultUniformBlocks::getDefaultUniformBlockBindingPoint(
    str_view name) noexcept
{
    auto const iterator{DefaultUniformBlocksBindings.cfind_if(
        [&name](UniformBlocksBindingType const& element) {
            return name == element.first;
        })};

    return iterator != DefaultUniformBlocksBindings.cend()
        ? static_cast<s32>(iterator->second)
        : -1;
}

}  // namespace haf::res
