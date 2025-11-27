module;

#include "types.hpp"

module htypes:growpolicy;

namespace htps
{
#pragma warning(push)
#pragma warning(disable : 4514)  // Unused functions in MSVC

class GrowPolicyUnary
{
public:
    static constexpr size_type growSize(size_type const size) noexcept
    {
        return size + 1U;
    }
};

class GrowPolicyDouble
{
public:
    static constexpr size_type growSize(size_type const size) noexcept
    {
        return size > 0U ? (size * 2U) : 1U;
    }
};

#pragma warning(pop)

}  // namespace htps

#endif
