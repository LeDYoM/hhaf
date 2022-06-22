#include <htypes/include/types.hpp>
#include <haf/include/scene/color.hpp>

namespace haf::scene
{
Color::value_type Color::ensureLimits_f32(htps::f32 source) noexcept
{
    return (source >= 255.0F)
        ? 255U
        : ((source <= 0.0) ? 0U : static_cast<Color::value_type>(source));
}

Color::Color() noexcept : r{value_min}, g{value_min}, b{value_min}, a{value_max}
{}

Color::Color(value_type const red,
             value_type const green,
             value_type const blue,
             value_type const alpha) noexcept :
    r{red}, g{green}, b{blue}, a{alpha}
{}

Color::Color(Color const& base_color, value_type const alpha) noexcept :
    r{base_color.r}, g{base_color.g}, b{base_color.b}, a{alpha}
{}

Color::Color(htps::u32 const color) noexcept :
    r{static_cast<value_type>((color & 0xFF000000) >> 24U)},
    g{static_cast<value_type>((color & 0x00FF0000) >> 16U)},
    b{static_cast<value_type>((color & 0x0000FF00) >> 8U)},
    a{static_cast<value_type>((color & 0x000000FF) >> 0U)}
{}

Color Color::fromFloats(htps::f32 const red,
                        htps::f32 const green,
                        htps::f32 const blue,
                        htps::f32 const alpha) noexcept
{
    return Color{static_cast<value_type>(red * value_max),
                 static_cast<value_type>(green * value_max),
                 static_cast<value_type>(blue * value_max),
                 static_cast<value_type>(alpha * value_max)};
}

Color& Color::operator*=(htps::f32 const delta) noexcept
{
    r = ensureLimits_f32(static_cast<htps::f32>(r) * delta);
    g = ensureLimits_f32(static_cast<htps::f32>(g) * delta);
    b = ensureLimits_f32(static_cast<htps::f32>(b) * delta);
    a = ensureLimits_f32(static_cast<htps::f32>(a) * delta);
    return *this;
}

Color& Color::operator/=(htps::f32 const delta) noexcept
{
    r = ensureLimits_f32(static_cast<htps::f32>(r) / delta);
    g = ensureLimits_f32(static_cast<htps::f32>(g) / delta);
    b = ensureLimits_f32(static_cast<htps::f32>(b) / delta);
    a = ensureLimits_f32(static_cast<htps::f32>(a) / delta);
    return *this;
}

Color::value_type Color::red() const noexcept
{
    return r;
}

Color::value_type Color::green() const noexcept
{
    return g;
}

Color::value_type Color::blue() const noexcept
{
    return b;
}

Color::value_type Color::alpha() const noexcept
{
    return a;
}

bool operator==(Color const& lhs, Color const& rhs) noexcept
{
    return (lhs.red() == rhs.red() && lhs.green() == rhs.green() &&
            lhs.blue() == rhs.blue() && lhs.alpha() == rhs.alpha());
}

bool operator!=(Color const& lhs, Color const& rhs) noexcept
{
    return !(lhs == rhs);
}

Color operator*(Color const& color, htps::f32 const delta) noexcept
{
    return Color{color} *= delta;
}

Color operator*(htps::f32 const delta, Color const& color) noexcept
{
    return Color{color} *= delta;
}

Color operator/(Color const& color, htps::f32 const delta) noexcept
{
    return Color{color} /= delta;
}

Color interpolate(Color const& begin, Color const& end, htps::f32 const delta)
{
    using namespace htps;
    f32 my_r{anim::interpolate(static_cast<f32>(begin.red()),
                               static_cast<f32>(end.red()), delta)};
    f32 my_g{anim::interpolate(static_cast<f32>(begin.green()),
                               static_cast<f32>(end.green()), delta)};
    f32 my_b{anim::interpolate(static_cast<f32>(begin.blue()),
                               static_cast<f32>(end.blue()), delta)};
    f32 my_a{anim::interpolate(static_cast<f32>(begin.alpha()),
                               static_cast<f32>(end.alpha()), delta)};

    return scene::Color{static_cast<u8>(my_r), static_cast<u8>(my_g),
                        static_cast<u8>(my_b), static_cast<u8>(my_a)};
}

}  // namespace haf::scene
