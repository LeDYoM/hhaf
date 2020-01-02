#include <menu_paged/include/menu_paged_option.hpp>

namespace lib::scene
{

MenuPagedOption::MenuPagedOption(str title, size_type start_index,
                                 size_type min, size_type max)
    : title_{std::move(title)}, on_selected_{NoAction},
      start_index_{std::move(start_index)}
{
    for (auto element = min; element <= max; ++element)
    {
        options_.push_back(make_str(element));
    }
}

MenuPagedOption::MenuPagedOption(str title, s32 on_selected)
    : title_{std::move(title)}, on_selected_{on_selected}, 
    start_index_{}, options_{} {}

MenuPagedOption::MenuPagedOption(str title, size_type start_index,
                                 string_vector options)
    : title_{std::move(title)}, on_selected_{NoAction},
      start_index_{start_index}
{
    options_ = std::move(options);
}

bool MenuPagedOption::hasOptions() const noexcept
{
    return !options_.empty();
}

string_vector MenuPagedOption::options() const noexcept
{
    return options_;
}

size_type MenuPagedOption::startIndex() const noexcept
{
    return start_index_;
}

s32 MenuPagedOption::onSelected() const noexcept
{
    return on_selected_;
}

}; // namespace lib::scene
