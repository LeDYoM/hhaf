HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_COLOR_INCLUDE_HPP
#define HAF_SCENE_COLOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <haf/include/animation/animable_types.hpp>

namespace haf::scene
{
/**
 * @brief Class representing a color. The suffix helps to
 * create custom specializations with more meaningful names.
 * This class contains red, green, value and alpha values
 * representing a color in the (r,g,b,a) space.
 *
 * @tparam value_type Type to represent the interal data values.
 */
struct Color
{
    using value_type = htps::u8;

    /**
     * @brief Maximum value for each coordinate
     */
    static constexpr value_type const value_max{255U};

    /**
     * @brief Minimum value for each coordinate
     */
    static constexpr value_type const value_min{0U};

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
    Color() noexcept;

    /**
     * @brief Construct a Color object from four values
     * @param red Red component of the color
     * @param green Green component of the color
     * @param blue Blue component of the color
     * @param alpha Alpha component of the color (Defaulted to opaque)
     */
    Color(value_type const red,
          value_type const green,
          value_type const blue,
          value_type const alpha = value_max) noexcept;

    Color(Color const&) noexcept = default;
    Color& operator=(Color const&) noexcept = default;
    Color(Color&&) noexcept                 = default;
    Color& operator=(Color&&) noexcept = default;

    /**
     * @brief Construct a Color object from another color, but with a
     * different alpha.
     * @param base_color The color that will give the r,g,b values
     * @param alpha The alpha value
     */
    Color(Color const& base_color, value_type const alpha) noexcept;

    explicit Color(htps::u32 const color) noexcept;

    static Color fromFloats(htps::f32 const red,
                            htps::f32 const green,
                            htps::f32 const blue,
                            htps::f32 const alpha = 1.0F) noexcept;

    Color& operator*=(htps::f32 const delta) noexcept;

    Color& operator/=(htps::f32 const delta) noexcept;

    value_type red() const noexcept;
    value_type green() const noexcept;
    value_type blue() const noexcept;
    value_type alpha() const noexcept;

private:
    /**
     * @brief Ensure that a value is between the required limits
     *
     * @tparam Source Type of the source value
     * @param source Source value of type Source
     * @return value_type Value of the type required for this Color
     */
    static value_type ensureLimits_f32(htps::f32 source) noexcept;

    value_type r;
    value_type g;
    value_type b;
    value_type a;
};

/**
 * @brief Equality comparation with another Color of the same type
 *
 * @param rhs Right part of the comparison
 * @return The colors are equal
 * @return The colors are not equal
 */
bool operator==(Color const& lhs, Color const& rhs) noexcept;

/**
 * @brief Unequality comparation with another Color of the same type
 *
 * @param rhs Right part of the comparison
 * @return The colors are not equal
 * @return The colors are equal
 */
bool operator!=(Color const& lhs, Color const& rhs) noexcept;

Color operator*(Color const& color, htps::f32 const delta) noexcept;
Color operator*(htps::f32 const delta, Color const& color) noexcept;

Color operator/(Color const& color, htps::f32 const delta) noexcept;

Color interpolate(Color const& begin, Color const& end, htps::f32 const delta);

namespace colors
{
static const Color Black{Color::value_min, Color::value_min, Color::value_min};
static const Color White{Color::value_max, Color::value_max, Color::value_max};
static const Color Red{Color::value_max, Color::value_min, Color::value_min};
static const Color Green{Color::value_min, Color::value_max, Color::value_min};
static const Color Blue{Color::value_min, Color::value_min, Color::value_max};
static const Color Yellow{Color::value_max, Color::value_max, Color::value_min};
static const Color Magenta{Color::value_max, Color::value_min,
                           Color::value_max};
static const Color Cyan{Color::value_min, Color::value_max, Color::value_max};
static const Color Transparent{Color::value_min, Color::value_min,
                               Color::value_min, Color::value_min};
}  // namespace colors

}  // namespace haf::scene

#endif
