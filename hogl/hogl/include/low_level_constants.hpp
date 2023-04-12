#ifndef HAF_OGL_LOW_LEVEL_CONSTANTS_INCLUDE_HPP
#define HAF_OGL_LOW_LEVEL_CONSTANTS_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <hogl/include/ogl_export.hpp>

namespace haf::ogl
{

// Private constants
struct HOGL_API LowLevelConstants
{
    static htps::s32 const f32vec1;
    static htps::s32 const f32vec2;
    static htps::s32 const f32vec3;
    static htps::s32 const f32vec4;
    static htps::s32 const s32vec1;
    static htps::s32 const f32mat4x4;
    static htps::s32 const sampler2D;
};

}  // namespace haf::ogl

#endif
