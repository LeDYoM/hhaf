#ifndef HAF_EXT_MENU_PAGED_OPTION_INCLUDE_HPP
#define HAF_EXT_MENU_PAGED_OPTION_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <menu_paged/include/range_option.hpp>
#include <menu_paged/include/page_options.hpp>

namespace haf::scene
{
/**
 * @brief This class stores the information to be passed to a @b MenuPage
 * in order to be used to create the @b MenuPaged via @b MenuPage::configure
 * It suports different variable types and actions to customize the behaviour
 * and display of a @b MenuPage.
 */
class MenuPagedOption
{
public:
    static constexpr htps::s32 NoAction = -3;
    static constexpr htps::s32 GoBack   = -2;
    static constexpr htps::s32 Accept   = -1;

    MenuPagedOption(htps::str title,
                    RangeOption range_options,
                    htps::s32 on_selected = NoAction);

    inline htps::str title() const noexcept { return title_; }
    const RangeOption& option() const noexcept { return option_; }
    htps::s32 onSelected() const noexcept;

private:
    htps::str title_;
    htps::s32 on_selected_;
    RangeOption option_;
};

template <typename... Args>
htps::sptr<MenuPagedOption> make_option(Args&&... args)
{
    return htps::msptr<MenuPagedOption>(std::forward<Args>(args)...);
}
}  // namespace haf::scene

#endif
