#ifndef HAF_EXT_PAGE_OPTIONS_OPTION_INCLUDE_HPP
#define HAF_EXT_PAGE_OPTIONS_OPTION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <menu_paged/include/range_option.hpp>

namespace haf::scene
{
class PageOptions
{
public:
    bool operator==(PageOptions const& other) const noexcept
    {
        return centered_empty_option == other.centered_empty_option;
    }
    bool centered_empty_option = false;
};

}  // namespace haf::scene

#endif
