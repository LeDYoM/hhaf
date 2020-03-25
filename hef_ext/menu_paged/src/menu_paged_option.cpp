#include <menu_paged/include/menu_paged_option.hpp>

namespace lib::scene
{

RangeOption::RangeOption(mtps::size_type min, mtps::size_type max)
    : options_(static_cast<mtps::size_type>(max - min))
{
    for (auto element = min; element <= max; ++element)
    {
        options_.push_back(mtps::make_str(element));
    }
}

RangeOption::RangeOption(mtps::string_vector options)
{
    options_ = std::move(options);
}

RangeOption::RangeOption() = default;

MenuPagedOption::MenuPagedOption(mtps::str title,
                                 RangeOption range_options,
                                 mtps::s32 on_selected)
    : title_{std::move(title)}, on_selected_{on_selected},
      option_{std::move(range_options)}
{
}

mtps::s32 MenuPagedOption::onSelected() const noexcept
{
    return on_selected_;
}

}; // namespace lib::scene
