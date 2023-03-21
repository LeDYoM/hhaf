#ifndef HAF_OGL_RENDER_SYSTEM_FUNCTIONS_INCLUDE_HPP
#define HAF_OGL_RENDER_SYSTEM_FUNCTIONS_INCLUDE_HPP

#include <hogl/include/ogl_export.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/vector4d.hpp>

namespace haf::ogl
{
[[nodiscard]] HOGL_API bool initOGL();
HOGL_API void setDebug(bool const enable);
HOGL_API void setDefaultRenderState();

void HOGL_API clearBackgroundColor(htps::vector4df const& color);
void HOGL_API clearDepthBuffer();

}  // namespace haf::ogl

#endif
