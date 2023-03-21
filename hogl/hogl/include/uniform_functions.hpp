#ifndef HAF_OGL_UNIFORM_FUNCTIONS_INCLUDE_HPP
#define HAF_OGL_UNIFORM_FUNCTIONS_INCLUDE_HPP

#include <hogl/include/types.hpp>
#include <htypes/include/span.hpp>

namespace haf::ogl
{
void setMatrixUniform(ogl::Handle const program, htps::s32 const location,
                      htps::s32 const size,
                      bool const transpose,
                      htps::f32 const* const data) noexcept;

}  // namespace haf::ogl

#endif
