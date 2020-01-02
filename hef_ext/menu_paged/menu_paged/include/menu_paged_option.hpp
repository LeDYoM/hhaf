#pragma once

#ifndef HEF_EXT_MENU_PAGED_OPTION_INCLUDE_HPP
#define HEF_EXT_MENU_PAGED_OPTION_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib::scene
{

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
                    size_type start_index, size_type min, size_type max);

    MenuPagedOption(str title, s32 on_selected = NoAction);

    MenuPagedOption(str title, size_type start_index, string_vector options);

    inline str title() const noexcept { return title_; }
    bool hasOptions() const noexcept;
    string_vector options() const noexcept;
    size_type startIndex() const noexcept;
    s32 onSelected() const noexcept;
private:
    str title_;
    s32 on_selected_;
    size_type start_index_;
    string_vector options_;
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
