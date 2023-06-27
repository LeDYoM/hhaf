FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_VVECTOR_INCLUDE_HPP
#define FACIL_MATH_VVECTOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/span.hpp>
#include <facil_math/include/vector3d.hpp>
#include <facil_math/include/matrix4x4.hpp>

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
        m_container.push_back(m_matrix * element);
    }

    constexpr void push_triangle(vector3d<T> const& element0,
                                 vector3d<T> const& element1,
                                 vector3d<T> const& element2)
    {
        push_back(element0);
        push_back(element1);
        push_back(element2);
    }

    constexpr void push_plane(const vector3d<T>& down_left_near,
                              const vector3d<T>& up_right_far)
    {
        auto const delta{up_right_far - down_left_near};
        vector3d<T> const down_right_far{down_left_near.x + delta.x, down_left_near.y,
                                     down_left_near.z + delta.z};
        vector3d<T> const up_left_far{down_left_near.x, down_left_near.y + delta.y,
                                     down_left_near.z + delta.z};
        push_triangle(down_left_near, down_right_far, up_right_far);
        push_triangle(up_right_far, up_left_far, down_left_near);
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

    constexpr void translate(vector3d<T> const& position) noexcept
    {
        m_matrix.translate(position);
    }

    constexpr void scale(vector3d<T> const& scale) noexcept
    {
        m_matrix.scale(scale);
    }

    constexpr void scale(T scale) noexcept
    {
        m_matrix.scale(scale);
    }

private:
    tps::vector<vector3d<T>> m_container;
    Matrix4x4 m_matrix;
};

}  // namespace fmath

#endif
