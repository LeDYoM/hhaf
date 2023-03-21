#include <hogl/include/types.hpp>
#include <htypes/include/types.hpp>
#include <glad/glad.h>

#include <type_traits>

namespace haf::ogl
{
static_assert(std::is_same_v<GLfloat, htps::f32>,
              "GLfloat and f32 must be the same type");
static_assert(std::is_same_v<GLuint, Handle>,
              "GLuint and Handle must be the same type");

constexpr Handle InvalidHandle{0U};

Handle invalidHandle() noexcept
{
    return InvalidHandle;
}

bool isValid(Handle const handle) noexcept
{
    return handle != InvalidHandle;
}

bool isInvalid(Handle const handle) noexcept
{
    return handle == InvalidHandle;
}

}  // namespace haf::ogl
