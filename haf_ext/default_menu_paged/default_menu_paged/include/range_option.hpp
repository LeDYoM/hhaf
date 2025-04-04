#ifndef HAF_EXT_DEFAULT_MENU_PAGED_RANGE_OPTION_INCLUDE_HPP
#define HAF_EXT_DEFAULT_MENU_PAGED_RANGE_OPTION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/menum.hpp>

namespace haf::exts::dmp
{
/**
 * @brief Option to select between two options
 */
class RangeOption
{
public:
    /**
     * @brief Construct a new Range Option object
     * @param min Index with the minimum index for the option.
     * @param max  Index with the maxumum index for the option
     */
    RangeOption(htps::size_type min, htps::size_type max);

    /**
     * @brief Construct a new Range Option object
     * @param options The options will be from 0 to options.size() -1
     */
    explicit RangeOption(htps::string_vector options);

    /**
     * @brief Construct a new Range Option object
     */
    explicit RangeOption();

    template <typename T>
    explicit RangeOption(T const) :
        options_(static_cast<htps::size_type>(htps::MEnum<T>::max_numeric -
                                              htps::MEnum<T>::min_numeric))
    {
        htps::MEnum<T> v{T::min};
        while (v.isValid())
        {
            options_.emplace_back(v.toStr());
            ++v;
        }
    }

    const htps::string_vector& options() const noexcept { return options_; }

private:
    htps::string_vector options_;
};
}  // namespace haf::exts::dmp

#endif
