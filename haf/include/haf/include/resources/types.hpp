HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_TYPES_INCLUDE_HPP
#define HAF_RESOURCES_TYPES_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::res
{

enum class BufferType : core::u32
{
    Unknown = 0U,
    Float   = 1U,
    Int     = 2
};

template <typename T>
constexpr core::u32 toTypeIndex() noexcept
{
    if constexpr (std::is_same_v<T, htps::f32>)
    {
        return static_cast<core::u32>(BufferType::Float);
    }
    else if constexpr (std::is_same_v<T, htps::s32>)
    {
        return static_cast<core::u32>(BufferType::Int);
    }
    else
    {
        return static_cast<core::u32>(BufferType::Unknown);
    }
}

struct VertexFormat
{
    BufferType bufferType{BufferType::Unknown};
    core::u32 numElements{0U};
    core::u32 arraySize{1U};
    bool operator==(VertexFormat const&) const = default;
};

}  // namespace haf::res

#endif
