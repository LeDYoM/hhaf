FMA_PRAGMA_ONCE
#ifndef FACIL_MATH_VVECTOR_INCLUDE_HPP
#define FACIL_MATH_VVECTOR_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>

namespace fmath
{
namespace tps = htps;

template <typename T>
class vvector
{
public:
    vvector() = default;

    template <tps::size_type N>
    constexpr void push_back(T const (&elements)[N])
    {
        for (tps::size_type i=0U;i<N;++i)
        {
            push_back(elements[i]);
        }
    }

    void push_back(T const& element)
    {
        m_container.push_back(element);
    }

    void push_back(T&& element)
    {
        m_container.push_back(tps::move(element));
    }

    void push_triangle(T const& element0, T const& element1, T const& element2)
    {
        m_container.push_back(element0);
        m_container.push_back(element1);
        m_container.push_back(element2);
    }

    void push_triangle(T&& element0, T&& element1, T&& element2)
    {
        m_container.push_back(tps::move(element0));
        m_container.push_back(tps::move(element1));
        m_container.push_back(tps::move(element2));
    }

    tps::vector<T> const& getVector() const noexcept
    {
        return m_container;
    }

private:
    tps::vector<T> m_container;

private:
};

}  // namespace fmath

#endif
