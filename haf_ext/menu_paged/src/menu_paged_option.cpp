#include <menu_paged/include/menu_paged_option.hpp>

using namespace htps;

namespace haf::scene
{
MenuPagedOption::MenuPagedOption(str title,
                                 RangeOption range_options,
                                 s32 on_selected) :
    title_{std::move(title)},
    on_selected_{on_selected},
    option_{std::move(range_options)}
{}

s32 MenuPagedOption::onSelected() const noexcept
{
    return on_selected_;
}

}  // namespace haf::scene
