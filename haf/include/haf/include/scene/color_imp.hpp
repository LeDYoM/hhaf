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
static constexpr value_type value_max = std::numeric_limits<value_type>::max();

template <typename value_type>
static constexpr value_type value_min = std::numeric_limits<value_type>::min();

template <typename Dest, typename Source>
constexpr Dest ensureLimits(Source source) noexcept
{
    return static_cast<Dest>(
        std::min(static_cast<Source>(value_max<Dest>),
                 std::max(source, static_cast<Source>(value_min<Dest>))));
}

template <typename value_type>
constexpr float normalize(const value_type v) noexcept
{
    return static_cast<float>(static_cast<float>(v) /
                              static_cast<float>(value_max<value_type>));
}

template <typename value_type>
constexpr void denormalize(const float v, value_type& d) noexcept
{
    d = static_cast<value_type>(v * value_max<value_type>);
}
}  // namespace detail

template <typename value_type>
struct ColorImp
{
    static constexpr value_type value_max = detail::value_max<value_type>;
    static constexpr value_type value_min = detail::value_min<value_type>;

    template <typename Source>
    static constexpr value_type ensureLimits(Source source) noexcept
    {
        return detail::ensureLimits<value_type, Source>(std::move(source));
    }

    constexpr ColorImp() noexcept : r{}, g{}, b{}, a{value_max} {}

    ColorImp(value_type const red,
             value_type const green,
             value_type const blue,
             value_type const alpha = value_max) noexcept :
        r{red}, g{green}, b{blue}, a{alpha}
    {}

    constexpr ColorImp(const ColorImp&) noexcept = default;
    constexpr ColorImp& operator=(const ColorImp&) noexcept = default;
    constexpr ColorImp(ColorImp&&) noexcept                 = default;
    constexpr ColorImp& operator=(ColorImp&&) noexcept = default;

    constexpr explicit ColorImp(const htps::u32 color) noexcept :
        r{static_cast<value_type>((color & 0xff000000) >> 24U)},
        g{static_cast<value_type>((color & 0x00ff0000) >> 16U)},
        b{static_cast<value_type>((color & 0x0000ff00) >> 8U)},
        a{static_cast<value_type>((color & 0x000000ff) >> 0U)}
    {}

    template <typename vt>
    constexpr ColorImp& operator=(const ColorImp<vt>& other) noexcept
    {
        r = ensureLimits(static_cast<value_type>(other.r));
        g = ensureLimits(static_cast<value_type>(other.g));
        b = ensureLimits(static_cast<value_type>(other.b));
        a = ensureLimits(static_cast<value_type>(other.a));
    }

    static constexpr ColorImp fromFloats(const float red,
                                         const float green,
                                         const float blue,
                                         const float alpha = 1.0F) noexcept
    {
        return ColorImp{static_cast<value_type>(red * value_max),
                        static_cast<value_type>(green * value_max),
                        static_cast<value_type>(blue * value_max),
                        static_cast<value_type>(alpha * value_max)};
    }

    template <typename vt>
    constexpr ColorImp(const ColorImp<vt>& other) noexcept
    {
        r = ensureLimits(static_cast<value_type>(other.r));
        g = ensureLimits(static_cast<value_type>(other.g));
        b = ensureLimits(static_cast<value_type>(other.b));
        a = ensureLimits(static_cast<value_type>(other.a));
    }

    constexpr bool operator==(const ColorImp& right) const noexcept
    {
        return (r == right.r && g == right.g && b == right.b && a == right.a);
    }

    constexpr bool operator!=(const ColorImp& right) const noexcept
    {
        return !(*this == right);
    }

    template <typename VT>
    constexpr ColorImp operator+(const ColorImp<VT>& right) const noexcept
    {
        return (ColorImp(*this) += right);
    }

    template <typename VT>
    constexpr ColorImp operator-(const ColorImp<VT>& right) const noexcept
    {
        return (ColorImp(*this) -= right);
    }

    template <typename VT>
    constexpr ColorImp operator*(const ColorImp<VT>& right) const noexcept
    {
        return (ColorImp(*this) *= right);
    }

    template <typename vt>
    constexpr ColorImp& operator+=(const ColorImp<vt>& right) noexcept
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
        r = static_cast<value_type>(static_cast<htps::u32>(r) * right.r /
                                    value_max);
        g = static_cast<value_type>(static_cast<htps::u32>(g) * right.g /
                                    value_max);
        b = static_cast<value_type>(static_cast<htps::u32>(b) * right.b /
                                    value_max);
        a = static_cast<value_type>(static_cast<htps::u32>(a) * right.a /
                                    value_max);
        return *this;
    }

    constexpr ColorImp& operator*=(const htps::f32 delta) noexcept
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

    constexpr value_type red() const noexcept { return r; }
    constexpr value_type green() const noexcept { return g; }
    constexpr value_type blue() const noexcept { return b; }
    constexpr value_type alpha() const noexcept { return a; }

  template<typename vt>
  friend struct ColorImp;

private:
    value_type r;
    value_type g;
    value_type b;
    value_type a;
};

template <typename vt>
constexpr ColorImp<vt> operator*(ColorImp<vt> color,
                                 const htps::f32 delta) noexcept
{
    return ColorImp<vt>{std::move(color)} *= delta;
}

template <typename vt>
constexpr ColorImp<vt> operator*(const htps::f32 delta,
                                 ColorImp<vt> color) noexcept
{
    return std::move(color) * delta;
}

template <typename vt>
constexpr ColorImp<vt> operator/(ColorImp<vt> color,
                                 const htps::f32 delta) noexcept
{
    return ColorImp<vt>{std::move(color)} /= delta;
}

template <typename vt>
constexpr ColorImp<vt> operator/(const htps::f32 delta,
                                 ColorImp<vt> color) noexcept
{
    return std::move(color) / delta;
}

}  // namespace haf::scene

#endif
