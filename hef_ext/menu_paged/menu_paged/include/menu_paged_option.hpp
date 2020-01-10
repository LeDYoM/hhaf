#pragma once

#ifndef HEF_EXT_MENU_PAGED_OPTION_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_OPTION_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/menum.hpp>

namespace lib::scene
{

class RangeOption
{
public:
    RangeOption(size_type min, size_type max);
    explicit RangeOption(string_vector options);
    explicit RangeOption();

    template <typename T>
    explicit RangeOption(T)
        : options_(static_cast<size_type>(MEnum<T>::max_numeric - MEnum<T>::min_numeric))
    {
        MEnum<T> v{T::min};
        while (v.isValid())
        {
            options_.emplace_back(v.toStr());
            ++v;
        }
    }

    const string_vector& options() const noexcept { return options_; }

private:
    string_vector options_;
};

/// This class stores the information to be passed to a @b MenuPage
/// in order to be used to create the @b MenuPaged via @b MenuPage::configure
/// It suports different variable types and actions to customize the behaviour
/// and display of a @b MenuPage.
class MenuPagedOption
{
public:
    static constexpr s32 NoAction = -3;
    static constexpr s32 GoBack = -2;
    static constexpr s32 Accept = -1;

    MenuPagedOption(str title,
                    RangeOption range_options,
                    s32 on_selected = NoAction);

    inline str title() const noexcept { return title_; }
    const RangeOption& option() const noexcept { return option_; }
    s32 onSelected() const noexcept;

private:
    str title_;
    s32 on_selected_;
    RangeOption option_;
};

class PageOptions
{
public:
    bool centered_empty_option = false;
};

template <typename... Args>
sptr<MenuPagedOption> make_option(Args &&... args)
{
    return msptr<MenuPagedOption>(std::forward<Args>(args)...);
}
} // namespace lib::scene

#endif
