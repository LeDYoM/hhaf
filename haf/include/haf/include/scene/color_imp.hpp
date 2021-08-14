#ifndef HAF_SCENE_COLOR_IMP_INCLUDE_HPP
#define HAF_SCENE_COLOR_IMP_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <algorithm>
#include <limits>

namespace haf::scene
{
namespace detail
{
template <typename value_type>
static constexpr value_type const value_max =
    std::numeric_limits<value_type>::max();

template <typename value_type>
static constexpr value_type const value_min =
    std::numeric_limits<value_type>::min();

template <typename Dest, typename Source>
constexpr Dest ensureLimits(Source const source) noexcept
{
    return static_cast<Dest>(
        std::min(static_cast<Source>(value_max<Dest>),
                 std::max(source, static_cast<Source>(value_min<Dest>))));
}

template <typename value_type>
constexpr htps::f32 normalize(value_type const v) noexcept
{
    return static_cast<htps::f32>(
        static_cast<htps::f32>(v) /
        static_cast<htps::f32>(value_max<value_type>));
}

template <typename value_type>
constexpr void denormalize(const htps::f32 v, value_type& d) noexcept
{
    d = static_cast<value_type>(v * value_max<value_type>);
}

}  // namespace detail

/**
 * @brief Class representing a color. The suffix helps to
 * create custom specializations with more meaningful names.
 * This class contains red, green, value and alpha values
 * representing a color in the (r,g,b,a) space.
 *
 * @tparam value_type Type to represent the interal data values.
 */
template <typename value_type>
struct ColorImp
{
    /**
     * @brief Maximum value for each coordinate
     */
    static constexpr value_type value_max = detail::value_max<value_type>;

    /**
     * @brief Minimum value for each coordinate
     */
    static constexpr value_type value_min = detail::value_min<value_type>;

    /**
     * @brief Ensure that a value is between the required limits
     *
     * @tparam Source Type of the source value
     * @param source Source value of type Source
     * @return value_type Value of the type required for this ColorImp
     */
    template <typename Source>
    static constexpr value_type ensureLimits(Source source) noexcept
    {
        return detail::ensureLimits<value_type, Source>(std::move(source));
    }

    /**
     * @brief Static constant defining the value for opaque colors
     */
    static constexpr value_type Opaque = value_max;

    /**
     * @brief Static constant defining the value for transparent colors
     */
    static constexpr value_type Transparent = value_min;

    /**
     * @brief Default constructor. Sets color to black opaque
     */
    constexpr ColorImp() noexcept :
        r{value_min}, g{value_min}, b{value_min}, a{value_max}
    {}

    /**
     * @brief Construct a ColorImp object from four values
     * @param red Red component of the color
     * @param green Green component of the color
     * @param blue Blue component of the color
     * @param alpha Alpha component of the color (Defaulted to opaque)
     */
    constexpr ColorImp(value_type const red,
                       value_type const green,
                       value_type const blue,
                       value_type const alpha = value_max) noexcept :
        r{red}, g{green}, b{blue}, a{alpha}
    {}

    constexpr ColorImp(ColorImp const&) noexcept = default;
    constexpr ColorImp& operator=(ColorImp const&) noexcept = default;
    constexpr ColorImp(ColorImp&&) noexcept                 = default;
    constexpr ColorImp& operator=(ColorImp&&) noexcept = default;

    /**
     * @brief Construct a ColorImp object from another color, but with a
     * different alpha.
     * @param base_color The color that will give the r,g,b values
     * @param alpha The alpha value
     */
    constexpr ColorImp(ColorImp const& base_color,
                       value_type const alpha) noexcept :
        r{base_color.r}, g{base_color.g}, b{base_color.b}, a{alpha}
    {}

    // TODO: Enable_if for value_type = u8
    constexpr explicit ColorImp(const htps::u32 color) noexcept :
        r{static_cast<value_type>((color & 0xFF000000) >> 24U)},
        g{static_cast<value_type>((color & 0x00FF0000) >> 16U)},
        b{static_cast<value_type>((color & 0x0000FF00) >> 8U)},
        a{static_cast<value_type>((color & 0x000000FF) >> 0U)}
    {}

    /**
     * @brief Copy assignment from a color from a different value_type
     *
     * @tparam vt Value type of the other color
     * @param other Other color
     * @return ColorImp& This color
     */
    template <typename vt>
    constexpr ColorImp& operator=(const ColorImp<vt>& other) noexcept
    {
        r = ensureLimits(static_cast<value_type>(other.r));
        g = ensureLimits(static_cast<value_type>(other.g));
        b = ensureLimits(static_cast<value_type>(other.b));
        a = ensureLimits(static_cast<value_type>(other.a));
        return *this;
    }

    static constexpr ColorImp fromFloats(htps::f32 const red,
                                         htps::f32 const green,
                                         htps::f32 const blue,
                                         htps::f32 const alpha = 1.0F) noexcept
    {
        return ColorImp{static_cast<value_type>(red * value_max),
                        static_cast<value_type>(green * value_max),
                        static_cast<value_type>(blue * value_max),
                        static_cast<value_type>(alpha * value_max)};
    }

    template <typename vt>
    constexpr ColorImp(ColorImp<vt> const& other) noexcept :
        r{ensureLimits(static_cast<value_type>(other.r))},
        g{ensureLimits(static_cast<value_type>(other.g))},
        b{ensureLimits(static_cast<value_type>(other.b))},
        a{ensureLimits(static_cast<value_type>(other.a))}
    {}

    /**
     * @brief Equality comparation with another ColorImp of the same type
     *
     * @param rhs Right part of the comparison
     * @return The colors are equal
     * @return The colors are not equal
     */
    constexpr bool operator==(ColorImp const& rhs) const noexcept
    {
        return (r == rhs.r && g == rhs.g && b == rhs.b && a == rhs.a);
    }

    /**
     * @brief Unequality comparation with another ColorImp of the same type
     *
     * @param rhs Right part of the comparison
     * @return The colors are not equal
     * @return The colors are equal
     */
    constexpr bool operator!=(ColorImp const& rhs) const noexcept
    {
        return !(*this == rhs);
    }

    /**
     * @brief Add two colors (They might be of different type). The result
     * is ensured to be a valid color of the source type
     * 
     * @tparam VT Value type of the second color
     * @param rhs  Right hand side operand
     * @return ColorImp with the resulting color
     */
    template <typename VT>
    constexpr ColorImp operator+(ColorImp<VT> const& rhs) const noexcept
    {
        return (ColorImp{*this} += rhs);
    }

    /**
     * @brief Substract two colors (They might be of different type). The result
     * is ensured to be a valid color of the source type
     * 
     * @tparam VT Value type of the second color
     * @param rhs  Right hand side operand
     * @return ColorImp with the resulting color
     */
    template <typename VT>
    constexpr ColorImp operator-(ColorImp<VT> const& rhs) const noexcept
    {
        return (ColorImp{*this} -= rhs);
    }

    /**
     * @brief Multiply two colors (They might be of different type). The result
     * is ensured to be a valid color of the source type
     * 
     * @tparam VT Value type of the second color
     * @param rhs  Right hand side operand
     * @return ColorImp with the resulting color
     */
    template <typename VT>
    constexpr ColorImp operator*(ColorImp<VT> const& rhs) const noexcept
    {
        return (ColorImp{*this} *= rhs);
    }

    template <typename vt>
    constexpr ColorImp& operator+=(ColorImp<vt> const& right) noexcept
    {
        r = ensureLimits(static_cast<vt>(r) + right.r);
        g = ensureLimits(static_cast<vt>(g) + right.g);
        b = ensureLimits(static_cast<vt>(b) + right.b);
        a = ensureLimits(static_cast<vt>(a) + right.a);
        return *this;
    }

    constexpr ColorImp& operator-=(const ColorImp& right) noexcept
    {
        r = ensureLimits(static_cast<htps::s32>(r) - right.r);
        g = ensureLimits(static_cast<htps::s32>(g) - right.g);
        b = ensureLimits(static_cast<htps::s32>(b) - right.b);
        a = ensureLimits(static_cast<htps::s32>(a) - right.a);
        return *this;
    }

    constexpr ColorImp& operator*=(const ColorImp& right) noexcept
    {
        r = static_cast<value_type>((static_cast<htps::u32>(r) * right.r) /
                                    value_max);
        g = static_cast<value_type>((static_cast<htps::u32>(g) * right.g) /
                                    value_max);
        b = static_cast<value_type>((static_cast<htps::u32>(b) * right.b) /
                                    value_max);
        a = static_cast<value_type>((static_cast<htps::u32>(a) * right.a) /
                                    value_max);
        return *this;
    }

    constexpr ColorImp& operator*=(htps::f32 const delta) noexcept
    {
        r = detail::ensureLimits<value_type>(static_cast<htps::f32>(r) * delta);
        g = detail::ensureLimits<value_type>(static_cast<htps::f32>(g) * delta);
        b = detail::ensureLimits<value_type>(static_cast<htps::f32>(b) * delta);
        a = detail::ensureLimits<value_type>(static_cast<htps::f32>(a) * delta);
        return *this;
    }

    constexpr ColorImp& operator/=(const htps::f32 delta) noexcept
    {
        r = detail::ensureLimits<value_type>(static_cast<htps::f32>(r) / delta);
        g = detail::ensureLimits<value_type>(static_cast<htps::f32>(g) / delta);
        b = detail::ensureLimits<value_type>(static_cast<htps::f32>(b) / delta);
        a = detail::ensureLimits<value_type>(static_cast<htps::f32>(a) / delta);
        return *this;
    }

    constexpr ColorImp operator*(htps::f32 const delta) const noexcept
    {
        return ColorImp{*this} *= delta;
    }

    constexpr ColorImp operator/(htps::f32 const delta) noexcept
    {
        return ColorImp{*this} /= delta;
    }

    constexpr value_type red() const noexcept { return r; }
    constexpr value_type green() const noexcept { return g; }
    constexpr value_type blue() const noexcept { return b; }
    constexpr value_type alpha() const noexcept { return a; }

    template <typename vt>
    friend struct ColorImp;

private:
    value_type r;
    value_type g;
    value_type b;
    value_type a;
};

template <typename vt>
constexpr ColorImp<vt> operator*(htps::f32 const delta,
                                 ColorImp<vt> const& color) noexcept
{
    return color * delta;
}

template <typename vt>
constexpr ColorImp<vt> operator/(htps::f32 const delta,
                                 ColorImp<vt> const& color) noexcept
{
    return color / delta;
}

}  // namespace haf::scene

#endif
