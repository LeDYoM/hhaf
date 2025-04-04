PARPAR_PRAGMA_ONCE
#ifndef PAR_PAR_MINI_INCLUDE_HPP
#define PAR_PAR_MINI_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str_view.hpp>

/**
 * @brief This file implements a small footprint version of parameter parser
 */
namespace parparmini
{
class ParametersParserMini
{
public:
    constexpr char const* param(const htps::u32 index) const noexcept
    {
        return ((index < m_argc) ? m_argv[index] : nullptr);
    }

    constexpr char const* operator[](const htps::u32 index) const noexcept
    {
        return param(index);
    }

    constexpr auto numParameters() const noexcept { return m_argc; }

private:
    bool param_starts_with(const htps::u32 index, char const* prefix)
    {
        htps::str_view v_prefix{prefix};
        htps::str_view v_param{param(index)};

        if (v_param.size() >= v_prefix.size())
        {
            return true;
        }
    }

    constexpr ParametersParserMini(int const argc,
                                   char const* const argv[]) noexcept :
        m_argc{static_cast<htps::u32>(argc)}, m_argv{argv}
    {}

    htps::u32 m_argc;
    char const* const* m_argv;

    friend ParametersParserMini create(int const argc, char const* const argv[]);
};

inline ParametersParserMini create(int const argc, char const* const argv[])
{
    return ParametersParserMini{argc, argv};
}

}  // namespace parparmini

#endif
