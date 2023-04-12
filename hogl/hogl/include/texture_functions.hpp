#ifndef HAF_OGL_SHADER_INCLUDE_HPP
#define HAF_OGL_SHADER_INCLUDE_HPP

#include <hogl/include/ogl_export.hpp>
#include <hogl/include/types.hpp>
#include <htypes/include/str.hpp>

namespace haf::ogl
{
[[nodiscard]] HOGL_API Handle createTexture() noexcept;
HOGL_API void destroyTexture(Handle const handle) noexcept;
}  // namespace haf::ogl

#endif
