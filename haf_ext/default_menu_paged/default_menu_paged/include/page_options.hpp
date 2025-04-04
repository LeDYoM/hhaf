#ifndef HAF_EXT_DEFAULT_MENU_PAGED_PAGE_OPTIONS_INCLUDE_HPP
#define HAF_EXT_DEFAULT_MENU_PAGED_PAGE_OPTIONS_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <default_menu_paged/include/range_option.hpp>

namespace haf::exts::dmp
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

}  // namespace haf::exts::dmp

#endif
