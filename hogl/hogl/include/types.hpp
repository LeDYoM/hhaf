#ifndef HAF_OGL_TYPES_INCLUDE_HPP
#define HAF_OGL_TYPES_INCLUDE_HPP

#include <hogl/include/ogl_export.hpp>
#include <htypes/include/types.hpp>
#include <htypes/include/vector4d.hpp>

namespace haf::ogl
{
using Handle = htps::u32;
HOGL_API bool isValid(Handle const handle) noexcept;
HOGL_API bool isInvalid(Handle const handle) noexcept;
[[nodiscard]] HOGL_API Handle invalidHandle() noexcept;

template <typename T>
HOGL_API constexpr htps::u32 toTypeIndex() noexcept
{
    if constexpr (std::is_same_v<T, htps::f32>)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

}  // namespace haf::ogl

#endif
