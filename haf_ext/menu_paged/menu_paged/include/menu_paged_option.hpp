#pragma once

#ifndef HEF_EXT_MENU_PAGED_OPTION_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_OPTION_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/menum.hpp>

namespace haf::scene
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
    RangeOption(mtps::size_type min, mtps::size_type max);

    /**
     * @brief Construct a new Range Option object
     * @param options The options will be from 0 to options.size() -1
     */
    explicit RangeOption(mtps::string_vector options);

    /**
     * @brief Construct a new Range Option object
     */
    explicit RangeOption();

    template <typename T>
    explicit RangeOption(T cons)
        : options_(static_cast<mtps::size_type>(mtps::MEnum<T>::max_numeric - mtps::MEnum<T>::min_numeric))
    {
        mtps::MEnum<T> v{T::min};
        while (v.isValid())
        {
            options_.emplace_back(v.toStr());
            ++v;
        }
    }

    const mtps::string_vector& options() const noexcept { return options_; }

private:
    mtps::string_vector options_;
};

/**
 * @brief This class stores the information to be passed to a @b MenuPage
 * in order to be used to create the @b MenuPaged via @b MenuPage::configure
 * It suports different variable types and actions to customize the behaviour
 * and display of a @b MenuPage.
 */
class MenuPagedOption
{
public:
    static constexpr mtps::s32 NoAction = -3;
    static constexpr mtps::s32 GoBack = -2;
    static constexpr mtps::s32 Accept = -1;

    MenuPagedOption(mtps::str title,
                    RangeOption range_options,
                    mtps::s32 on_selected = NoAction);

    inline mtps::str title() const noexcept { return title_; }
    const RangeOption& option() const noexcept { return option_; }
    mtps::s32 onSelected() const noexcept;

private:
    mtps::str title_;
    mtps::s32 on_selected_;
    RangeOption option_;
};

class PageOptions
{
public:
    bool centered_empty_option = false;
};

template <typename... Args>
mtps::sptr<MenuPagedOption> make_option(Args &&... args)
{
    return mtps::msptr<MenuPagedOption>(std::forward<Args>(args)...);
}
} // namespace haf::scene

#endif
