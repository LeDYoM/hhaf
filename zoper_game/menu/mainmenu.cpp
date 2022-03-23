#include "mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../gameshareddata.hpp"
#include <menu_paged/include/menu_page.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <haf/include/scene/scene.hpp>
#include <haf/include/scene_components/camera_component.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/shareddata/ishared_data.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/types.hpp>

using namespace htps;
using namespace haf;
using namespace haf::scene;
using namespace haf::scene::nodes;

namespace zoper
{

enum class Antialiasing
{
    Worst,
    Bad,
    Normal,
    Good,
    Best,
    min = Worst,
    max = Best
};

constexpr auto to_str(Antialiasing const aa)
{
    switch (aa)
    {
        case Antialiasing::Worst:
            return "Worst";
            break;
        case Antialiasing::Bad:
            return "Bad";
            break;
        case Antialiasing::Normal:
            return "Normal";
            break;
        case Antialiasing::Good:
            return "Good";
            break;
        case Antialiasing::Best:
            return "Best";
            break;
        default:
            return "";
    }
}

void MainMenu::goGame(GameMode const game_mode, vector<s32> menu_data)
{
    using namespace haf::shdata;
    auto game_shared_data_updater{
        SharedDataUpdater<GameSharedData>{subSystem<ISharedData>()}};

    auto game_shared_data{
        game_shared_data_updater.updateOrCreate(GameSharedData::address())};

    game_shared_data->startLevel = menu_data[0U];
    game_shared_data->gameMode   = game_mode;
    DisplayLog::info(game_shared_data->to_str());

    terminate(MenuFinishedStatus::Forward);
}

void MainMenu::goTimeGame(vector<s32> menu_data)
{
    goGame(GameMode::Time, std::move(menu_data));
}

void MainMenu::goTokenGame(vector<s32> menu_data)
{
    goGame(GameMode::Token, std::move(menu_data));
}

void MainMenu::onCreated()
{
    BaseClass::onCreated();

    prop<MenuPagedProperties>()
        .put<NormalTextFont>(
#ifdef TEST_BMP_FONT
            getBMPFont(MainMenuResources::TestFontId)
#else
            subSystem<res::IResourceRetriever>()
                ->getTTFont(MainMenuResources::MenuFontId)
                ->font(30)
#endif
                )
        .put<NormalColor>(colors::Blue)
        .put<SelectedColor>(colors::Red);

    vector_shared_pointers<scene::MenuPage> menu_steps;
    prop<Scale>() = Scale::value_type{1.0F, 0.3F};

    // Create and register menu pages
    {
        PageOptions main_page_options{true};
        auto menuPageMain{createMenuPage(
            "menuPageMain")};
        menuPageMain->menu_options =
            vector_shared_pointers<MenuPagedOption>{
                make_option("Play Token mode", RangeOption(), 1),
                make_option("Play Time mode", RangeOption(), 2),
                make_option("Options", RangeOption(), 3),
                make_option("Exit", RangeOption(), MenuPagedOption::GoBack)};
//        menuPageMain->menu_page_options = main_page_options;

        menu_steps.emplace_back(std::move(menuPageMain));
    }

    {
        auto menuPageByToken{createMenuPage(
            "menuPageByToken")};
        menuPageByToken->menu_options =
            vector_shared_pointers<MenuPagedOption>{
                make_option("Start level Token Mode", RangeOption(1U, 10U)),
                make_option("Play", RangeOption(), MenuPagedOption::Accept),
                make_option("Back", RangeOption(), MenuPagedOption::GoBack)};

        menu_steps.emplace_back(std::move(menuPageByToken));
    }
    menu_steps.back()->Accepted.connect(
        make_function(this, &MainMenu::goTokenGame));
    {
        auto menuPageByTime{createMenuPage(
            "menuPageByTime")};
            menuPageByTime->menu_options =
            vector_shared_pointers<MenuPagedOption>{
                make_option("Start level Time Mode", RangeOption(1U, 10U)),
                make_option("Play", RangeOption(), MenuPagedOption::Accept),
                make_option("Back", RangeOption(), MenuPagedOption::GoBack)};

        menu_steps.emplace_back(std::move(menuPageByTime));
    }

    menu_steps.back()->Accepted.connect(
        make_function(this, &MainMenu::goTimeGame));

    {
        auto menuPageOptions{createMenuPage(
            "menuPageOptions")};
            menuPageOptions->menu_options = vector_shared_pointers<MenuPagedOption>{
                make_option("Antialiasing", RangeOption{Antialiasing{}}),
                make_option("Resolution",
                            RangeOption(string_vector{"Worst", "Bad", "Normal",
                                                      "Good", "Best"})),
                make_option("Fullscreen",
                            RangeOption(string_vector{"No", "Yes"})),
                make_option("VSync", RangeOption(string_vector{"No", "Yes"})),
                make_option("Redefine keyboard", RangeOption()),
                make_option("Accept", RangeOption(), MenuPagedOption::GoBack),
                make_option("Cancel", RangeOption(),
                            MenuPagedOption::GoBack)};

        menu_steps.emplace_back(std::move(menuPageOptions));
    }

    configure_menu(std::move(menu_steps));

    prop<FinishSceneAtEnd>() = true;
}

}  // namespace zoper
