HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RESOURCE_VERTEX_FORMATS_INCLUDE_HPP
#define HAF_RENDER_RESOURCE_VERTEX_FORMATS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <haf/include/render/types.hpp>

namespace haf::render
{
template <typename T>
consteval core::u32 getkNumElements() noexcept
{
    if constexpr (requires { T::kNumElements; })
    {
        return static_cast<core::u32>(T::kNumElements);
    }
    else
    {
        return static_cast<core::u32>(1U);
    }
}

template <typename T>
consteval VertexFormat getVertexFormat() noexcept
{
    return VertexFormat{toBufferType<T>(), getkNumElements<T>(), 1U};
}

}  // namespace haf::render

#endif
