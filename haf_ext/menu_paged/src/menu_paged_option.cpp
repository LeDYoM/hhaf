#include <menu_paged/include/menu_paged_option.hpp>

using namespace htps;

namespace haf::scene
{
MenuPagedOption::MenuPagedOption(str title,
                                 RangeOption range_options,
                                 s32 on_selected) :
    title_{htps::move(title)},
    on_selected_{on_selected},
    option_{htps::move(range_options)}
{}

s32 MenuPagedOption::onSelected() const noexcept
{
    return on_selected_;
}

str const& MenuPagedOption::title() const noexcept
{
    return title_;
}

RangeOption const& MenuPagedOption::option() const noexcept
{
    return option_;
}

}  // namespace haf::scene
