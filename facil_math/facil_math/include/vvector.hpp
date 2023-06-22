FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_VVECTOR_INCLUDE_HPP
#define FACIL_MATH_VVECTOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/span.hpp>
#include <facil_math/include/vector3d.hpp>

namespace fmath
{
namespace tps = htps;

template <typename T>
class vvector3d
{
public:
    constexpr vvector3d() = default;

    template <tps::size_type N>
    constexpr void push_back(vector3d<T> const (&elements)[N])
    {
        for (tps::size_type i = 0U; i < N; ++i)
        {
            push_back(elements[i]);
        }
    }

    constexpr void push_back(vector3d<T> const& element)
    {
        m_container.push_back(element);
    }

    constexpr void push_back(vector3d<T>&& element)
    {
        m_container.push_back(tps::move(element));
    }

    constexpr void push_triangle(vector3d<T> const& element0,
                                 vector3d<T> const& element1,
                                 vector3d<T> const& element2)
    {
        m_container.push_back(element0);
        m_container.push_back(element1);
        m_container.push_back(element2);
    }

    constexpr void push_triangle(vector3d<T>&& element0,
                                 vector3d<T>&& element1,
                                 vector3d<T>&& element2)
    {
        m_container.push_back(tps::move(element0));
        m_container.push_back(tps::move(element1));
        m_container.push_back(tps::move(element2));
    }

    constexpr void push_plane(const vector3d<T>& down_left,
                              const vector3d<T>& up_right)
    {
        auto const delta{up_right - down_left};
        vector3d<T> const triangle_0{down_left.x + delta.x, down_left.y,
                                     down_left.z};
        vector3d<T> const triangle_1{down_left.x + delta.x,
                                     down_left.y + delta.y,
                                     down_left.z + delta.z};
        vector3d<T> const triangle_2{down_left.x, down_left.y + delta.y,
                                     down_left.z + delta.z};
        push_triangle(down_left, triangle_0, triangle_1);
        push_triangle(triangle_1, triangle_2, triangle_0);
    }

    constexpr tps::vector<vector3d<T>> const& getVector() const noexcept
    {
        return m_container;
    }

    constexpr operator tps::span<vector3d<T> const>() const noexcept
    {
        return tps::span{m_container};
    }

    constexpr tps::span<vector3d<T> const> as_span() const noexcept
    {
        return static_cast<tps::span<vector3d<T> const>>(*this);
    }

private:
    tps::vector<vector3d<T>> m_container;

private:
};

}  // namespace fmath

#endif
