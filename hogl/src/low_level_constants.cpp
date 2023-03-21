#include <hogl/include/low_level_constants.hpp>
#include <htypes/include/types.hpp>
#include <glad/glad.h>

using namespace htps;

namespace haf::ogl
{
s32 const LowLevelConstants::f32vec2{GL_FLOAT_VEC2};
s32 const LowLevelConstants::f32vec3{GL_FLOAT_VEC3};
s32 const LowLevelConstants::f32vec4{GL_FLOAT_VEC4};
s32 const LowLevelConstants::f32vec1{GL_FLOAT};
s32 const LowLevelConstants::s32vec1{GL_INT};
s32 const LowLevelConstants::f32mat4x4{GL_FLOAT_MAT4};

}  // namespace haf::ogl
