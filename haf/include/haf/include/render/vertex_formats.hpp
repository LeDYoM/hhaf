HTPS_PRAGMA_ONCE
#ifndef HAF_RENDER_RESOURCE_VERTEX_FORMATS_INCLUDE_HPP
#define HAF_RENDER_RESOURCE_VERTEX_FORMATS_INCLUDE_HPP

#include <haf/include/haf_export.hpp>
#include <haf/include/core/types.hpp>
#include <haf/include/render/types.hpp>
#include <haf/include/core/matrix4x4.hpp>

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
consteval core::u32 getkNumSubElements() noexcept
{
    if constexpr (requires { T::kNumSubElements; })
    {
        return static_cast<core::u32>(T::kNumSubElements);
    }
    else
    {
        return static_cast<core::u32>(1U);
    }
}

template <typename T>
concept HasInnerValueType = requires
{
    typename T::value_type;
};

template <typename T>
constexpr core::u32 structSize() noexcept
{
    if constexpr (
        requires { T::kNumElements; } && requires { typename T::value_type; })
    {
        return T::kNumElements * sizeof(T::value_type);
    }
    else if constexpr (requires { typename T::value_type; })
    {
        return structSize<typename T::value_type>();
    }
    else
    {
        return sizeof(T);
    }
}

template <typename T>
struct GetValueType
{
    using value_type = T;
};

template <typename T>
requires HasInnerValueType<T> struct GetValueType<T>
{
    using value_type = typename T::value_type;
};

template <typename T>
consteval VertexFormatWithoutOffset getVertexFormatWithoutOffset() noexcept
{
    using value_type = typename GetValueType<T>::value_type;
    return VertexFormatWithoutOffset{toBufferType<value_type>(),
                                     getkNumElements<T>(), 1U};
}

template <typename T>
consteval static auto getVertexFormats() noexcept
{
    if constexpr (requires { T::getVertexFormats(); })
    {
        return T::getVertexFormats();
    }
    else
    {
        return core::array<VertexFormat, 1U>{
            VertexFormat{getVertexFormatWithoutOffset<T>()}};
    }
}

template <typename T>
struct Position3Normal3TextureCoordinates2
{
    core::vector3d<T> position;
    core::vector3d<T> normal;
    core::vector2d<T> textureuv;
    static constexpr core::u32 kNumElements{decltype(position)::kNumElements +
                                            decltype(normal)::kNumElements +
                                            decltype(textureuv)::kNumElements};
    static constexpr core::u32 kNumSubElements{3U};

    static consteval core::array<VertexFormat, kNumSubElements>
    getVertexFormats() noexcept
    {
        return core::array<VertexFormat, 3U>{
            {getVertexFormatWithoutOffset<core::vector3df>(),
             offsetof(Position3Normal3TextureCoordinates2, position)},
            {getVertexFormatWithoutOffset<core::vector3df>(),
             offsetof(Position3Normal3TextureCoordinates2, normal)},
            {getVertexFormatWithoutOffset<core::vector2df>(),
             offsetof(Position3Normal3TextureCoordinates2, textureuv)}};
    }

    using value_type = T;
};

using Position3fNormal3fTextureCoordinates2f =
    Position3Normal3TextureCoordinates2<core::f32>;

struct CameraData
{
    math::Matrix4x4 projection;
    static constexpr core::u32 kNumElements{decltype(projection)::kNumElements};
    static constexpr core::u32 kNumSubElements{1U};

    static consteval core::array<VertexFormat, kNumSubElements>
    getVertexFormats() noexcept
    {
        return core::array<VertexFormat, 1U>{
            {getVertexFormatWithoutOffset<math::Matrix4x4>(),
             offsetof(CameraData, projection)}};
    }

    using value_type = core::f32;
};

}  // namespace haf::render

#endif
