#ifndef HAF_BACKEND_DEV_IVERTEX_INCLUDE_HPP
#define HAF_BACKEND_DEV_IVERTEX_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <facil_math/include/vector2d.hpp>

namespace haf::backend
{
using iPosition           = fmath::vector2d<htps::f32>;
using iTextureCoordinates = fmath::vector2d<htps::f32>;

struct iColor final
{
    htps::u8 r;
    htps::u8 g;
    htps::u8 b;
    htps::u8 a;
};

struct Vertex
{
    iPosition position;
    iColor color;
    iTextureCoordinates texture_coordinates;
    static constexpr htps::size_type PositionOffset{0U};
    using PositionElementType = htps::f32;
    static constexpr htps::size_type PositionElementSize{
        sizeof(PositionElementType)};
    static constexpr htps::size_type PositionElements{2U};
    //////////////////////////////////////////////////////////////
    static constexpr htps::size_type ColorOffset{
        PositionOffset + (PositionElementSize * PositionElements)};
    using ColorElementType = htps::u8;
    static constexpr htps::size_type ColorElementSize{sizeof(ColorElementType)};
    static constexpr htps::size_type ColorElements{4U};
    /////////////////////////////////////////////////////////////
    static constexpr htps::size_type TextureRectOffset{
        ColorOffset + (ColorElementSize * ColorElements)};
    using TextureRectElementType = htps::f32;
    static constexpr htps::size_type TextureRectElementSize{
        sizeof(TextureRectElementType)};
    static constexpr htps::size_type TextureRectElements{2U};

    static inline const void* PositionData() noexcept
    {
        return reinterpret_cast<const void*>(PositionOffset);
    }

    static inline auto ColorData() noexcept
    {
        return reinterpret_cast<const void*>(ColorOffset);
    }

    static inline const void* TextureRectData() noexcept
    {
        return reinterpret_cast<const void*>(TextureRectOffset);
    }
};

enum class VertexAttributes : htps::u8
{
    Positions          = 0U,
    Colors             = 1U,
    TextureCoordinates = 2U
};

}  // namespace haf::backend

#endif
