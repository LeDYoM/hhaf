#include <menu_paged/include/range_option.hpp>

using namespace htps;

namespace haf::scene
{
RangeOption::RangeOption(size_type min, size_type max) :
    options_(static_cast<size_type>(max - min))
{
    for (auto element = min; element <= max; ++element)
    {
        options_.emplace_back(make_str(element));
    }
}

RangeOption::RangeOption(string_vector options) : options_{std::move(options)}
{}

RangeOption::RangeOption() = default;

}  // namespace haf::scene
