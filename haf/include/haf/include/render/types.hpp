HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_TYPES_INCLUDE_HPP
#define HAF_RESOURCES_TYPES_INCLUDE_HPP

#include <haf/include/core/types.hpp>

namespace haf::render
{

enum class BufferType : core::u32
{
    Unknown = 0U,
    Float   = 1U,
    Int     = 2U,
    Sampler = 3U
};

enum class BufferUsage
{
    Static  = 0U,
    Dynamic = 1U
};

enum class BufferMode
{
    Draw = 0U
};

template <typename T>
consteval BufferType toBufferType() noexcept
{
    if constexpr (std::is_same_v<T, htps::f32>)
    {
        return BufferType::Float;
    }
    else if constexpr (std::is_same_v<T, htps::s32>)
    {
        return BufferType::Int;
    }
    else
    {
        //        static_assert(false);
        return BufferType::Unknown;
    }
}

constexpr core::u32 sizeOfBufferType(BufferType const bufferType) noexcept
{
    switch (bufferType)
    {
        case BufferType::Float:
        case BufferType::Sampler:
            return sizeof(core::f32);
            break;
        case BufferType::Int:
            return sizeof(core::s32);
            break;
        case BufferType::Unknown:
            return 0U;
            break;
    }
    return 0U;
}

template <typename T>
consteval core::u32 toTypeIndex() noexcept
{
    return static_cast<core::u32>(toBufferType<T>());
}

struct VertexFormatWithoutOffset
{
    BufferType bufferType{BufferType::Unknown};
    core::u32 numElements{0U};
    core::u32 arraySize{1U};
    bool operator==(VertexFormatWithoutOffset const&) const = default;
};

struct VertexFormat : VertexFormatWithoutOffset
{
    core::u32 offset{0U};
    bool operator==(VertexFormat const&) const = default;
};

constexpr core::u32 sizeOfVertexFormat(
    VertexFormatWithoutOffset const& vertexFormatWithoutOffset) noexcept
{
    return sizeOfBufferType(vertexFormatWithoutOffset.bufferType) *
        vertexFormatWithoutOffset.arraySize *
        vertexFormatWithoutOffset.numElements;
}

constexpr core::u32 sizeOfVertexFormat(
    VertexFormat const& vertexFormat) noexcept
{
    return sizeOfVertexFormat(
        static_cast<VertexFormatWithoutOffset>(vertexFormat));
}

}  // namespace haf::render

#endif
