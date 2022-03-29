#ifndef ZOPER_MAINMENU_INCLUDE_HPP
#define ZOPER_MAINMENU_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/vector.hpp>
#include <menu_paged/include/menu_paged.hpp>

namespace zoper
{
enum class GameMode : htps::u8;

class MainMenu : public haf::scene::MenuPaged
{
public:
    using BaseClass = haf::scene::MenuPaged;
    using BaseClass::prop;

    static constexpr char StaticTypeName[] = "MainMenu";
    using BaseClass::BaseClass;

    virtual void onCreated() override;

private:
    void onTableNodeCreated(
        htps::vector2dst,
        htps::sptr<haf::scene::nodes::SceneNodeText> const&);
    void goTimeGame(htps::vector<htps::s32> menu_data);
    void goTokenGame(htps::vector<htps::s32> menu_data);
    void goGame(GameMode const game_mode, htps::vector<htps::s32> menu_data);
};
}  // namespace zoper

#endif