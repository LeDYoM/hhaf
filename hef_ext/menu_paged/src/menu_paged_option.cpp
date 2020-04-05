#include <menu_paged/include/menu_paged_option.hpp>

using namespace mtps;

namespace haf::scene
{
RangeOption::RangeOption(size_type min, size_type max) :
    options_(static_cast<size_type>(max - min))
{
    for (auto element = min; element <= max; ++element)
    {
        options_.push_back(make_str(element));
    }
}

RangeOption::RangeOption(string_vector options)
{
    options_ = std::move(options);
}

RangeOption::RangeOption() = default;

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

};  // namespace haf::scene
