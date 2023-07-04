FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_VVECTOR_INCLUDE_HPP
#define FACIL_MATH_VVECTOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/array.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/span.hpp>
#include <facil_math/include/vector_types.hpp>
#include <facil_math/include/matrix4x4.hpp>

namespace fmath
{
namespace tps = htps;

template <tps::u8 SIZE, typename T>
class vvector
{
public:
    using this_vector = vector_type_t<SIZE, T>;

    constexpr vvector() = default;

    template <tps::size_type N>
    constexpr void push_back(this_vector const (&elements)[N])
    {
        for (tps::size_type i{0U}; i < N; ++i)
        {
            push_back(elements[i]);
        }
    }

    constexpr void push_back(this_vector const& element)
    {
        m_container.push_back(m_matrix * element);
    }

    template <typename V>
    constexpr void push_triangle(V&& element0, V&& element1, V&& element2)
    {
        push_back(this_vector{element0});
        push_back(this_vector{element1});
        push_back(this_vector{element2});
    }

    constexpr void push_triangle(this_vector const& element0,
                                 this_vector const& element1,
                                 this_vector const& element2)
    {
        push_back(element0);
        push_back(element1);
        push_back(element2);
    }

    constexpr void push_triangle(this_vector&& element0,
                                 this_vector&& element1,
                                 this_vector&& element2)
    {
        push_back(tps::move(element0));
        push_back(tps::move(element1));
        push_back(tps::move(element2));
    }

    constexpr void push_triangle(tps::array<this_vector, 3U> elements)
    {
        push_back(tps::move(elements[0]));
        push_back(tps::move(elements[1]));
        push_back(tps::move(elements[2]));
    }

    constexpr tps::vector<this_vector> const& getVector() const noexcept
    {
        return m_container;
    }

    constexpr operator tps::span<this_vector const>() const noexcept
    {
        return tps::span{m_container};
    }

    constexpr tps::span<this_vector const> as_span() const noexcept
    {
        return static_cast<tps::span<this_vector const>>(*this);
    }

    constexpr void translate(vector3d<T> const& position) noexcept
    {
        m_matrix.translate(position);
    }

    constexpr void scale(vector3d<T> const& scale) noexcept
    {
        m_matrix.scale(scale);
    }

    constexpr void scale(T scale) noexcept { m_matrix.scale(scale); }

private:
    tps::vector<this_vector> m_container;
    Matrix4x4 m_matrix;
};

template <typename T>
using vvector2d = vvector<2U, T>;

template <typename T>
using vvector3d = vvector<3U, T>;

template <typename T>
using vvector4d = vvector<4U, T>;

}  // namespace fmath

#endif
