PARPAR_PRAGMA_ONCE
#ifndef PAR_PAR_MINI_INCLUDE_HPP
#define PAR_PAR_MINI_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str_functions.hpp>
#include <htypes/include/str_view.hpp>

/**
 * @brief This file implements a small footprint version of parameter parser
 */
namespace parparmini
{
class ParametersParserMini
{
public:
    using Index = htps::u32;

    [[nodiscard]] constexpr auto operator[](Index const index) const noexcept
    {
        return htps::str_view{(index < m_argc) ? m_argv[index] : nullptr};
    }

    [[nodiscard]] constexpr auto param(Index const index) const noexcept
    {
        return (*this)[index];
    }

    [[nodiscard]] constexpr auto paramKey(Index const index) const noexcept
    {
        auto const pr{param(index)};
        if (pr != nullptr)
        {
            if (pr[0] != '-')
            {
                return pr;
            }
            else if (pr[1] != '-')
            {
                return pr.offset(1);
            }
            else
            {
                return pr.offset(2);
            }
        }
        return htps::str_view{};
    }

    [[nodiscard]] constexpr auto paramValue(Index const index) const noexcept
    {
        return paramKey(index + 1U);
    }

    [[nodiscard]] constexpr auto operator[](htps::str_view index) const noexcept
    {
        for (auto i{1U}; i < m_argc; ++i)
        {
            if (param(i) == index)
            {
                return i;
            }
        }
        return 0U;
    }

    [[nodiscard]] constexpr auto paramKey(
        htps::str_view const index) const noexcept
    {
        for (auto i{1U}; i < m_argc; ++i)
        {
            if (paramKey(i) == index)
            {
                return i;
            }
        }
        return 0U;
    }

    [[nodiscard]] constexpr auto param(htps::str_view index) const noexcept
    {
        return (*this)[htps::move(index)];
    }

    [[nodiscard]] constexpr auto paramValue(htps::str_view index) const noexcept
    {
        auto const key{paramKey(index)};
        return ((key > 0U) ? paramValue(key) : htps::str_view{});
    }

    [[nodiscard]] constexpr auto numParameters() const noexcept
    {
        return m_argc;
    }

private:
    [[nodiscard]] constexpr ParametersParserMini(
        int const argc,
        char const* const argv[]) noexcept :
        m_argc{static_cast<Index>(argc)}, m_argv{argv}
    {}

    Index m_argc;
    char const* const* m_argv;

    friend ParametersParserMini create(int const argc,
                                       char const* const argv[]);
};

inline [[nodiscard]] ParametersParserMini create(int const argc,
                                                 char const* const argv[])
{
    return ParametersParserMini{argc, argv};
}

}  // namespace parparmini

#endif
