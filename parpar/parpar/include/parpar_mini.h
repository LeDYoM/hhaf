PARPAR_PRAGMA_ONCE
#ifndef PAR_PAR_MINI_INCLUDE_HPP
#define PAR_PAR_MINI_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str_functions.hpp>

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
        return ((index < m_argc) ? m_argv[index] : nullptr);
    }

    [[nodiscard]] constexpr auto param(Index const index) const noexcept
    {
        return (*this)[index];
    }

    [[nodiscard]] constexpr auto numParameters() const noexcept
    {
        return m_argc;
    }

    [[nodiscard]] constexpr auto paramKey(Index const index) const noexcept
    {
        auto const pr{param(index)};
        if (pr != nullptr)
        {
            if (pr[0] != '-')
            {
                return &(pr[0]);
            }
            else if (pr[1] != '-')
            {
                return &(pr[1]);
            }
            else
            {
                return &(pr[2]);
            }
        }
        return static_cast<const char*>(nullptr);
    }

private:
    bool param_starts_with(Index const index, char const* prefix)
    {
        auto const current_param{param(index)};
        return htps::starts_with(current_param, prefix);
    }

    constexpr ParametersParserMini(int const argc,
                                   char const* const argv[]) noexcept :
        m_argc{static_cast<Index>(argc)}, m_argv{argv}
    {}

    Index m_argc;
    char const* const* m_argv;

    friend ParametersParserMini create(int const argc,
                                       char const* const argv[]);
};

inline ParametersParserMini create(int const argc, char const* const argv[])
{
    return ParametersParserMini{argc, argv};
}

}  // namespace parparmini

#endif
