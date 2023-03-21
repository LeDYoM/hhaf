#ifndef HAF_OGL_BUFFER_FUNCTIONS_INCLUDE_HPP
#define HAF_OGL_BUFFER_FUNCTIONS_INCLUDE_HPP

#include <hogl/include/types.hpp>
#include <htypes/include/span.hpp>

namespace haf::ogl
{
Handle createRenderBuffer(void const* const data, htps::s32 const size);

template <typename T>
Handle createRenderBuffer(htps::span<T> const data)
{
    return createRenderBuffer(static_cast<const void*>(data.cbegin()),
                              data.size() * sizeof(T));
}

}  // namespace haf::ogl

#endif
