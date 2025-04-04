#ifndef ZOPER_MAINMENU_INCLUDE_HPP
#define ZOPER_MAINMENU_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <default_menu_paged/include/menu_paged.hpp>

namespace zoper
{
enum class GameMode : htps::u8;

class MainMenu : public haf::exts::dmp::MenuPaged
{
public:
    using Base = haf::exts::dmp::MenuPaged;

    static constexpr char StaticTypeName[] = "MainMenu";
    using Base::Base;

    virtual void onAttached() override;

private:
    void onTableNodeCreated(fmath::vector2dst,
                            htps::sptr<haf::scene::Text> const&);
    void goTimeGame(htps::vector<htps::s32> menu_data);
    void goTokenGame(htps::vector<htps::s32> menu_data);
    void goGame(GameMode const game_mode, htps::vector<htps::s32> menu_data);
};
}  // namespace zoper

#endif