#include "mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../gameshareddata.hpp"
#include "../zoperprogramcontroller.hpp"
#include <menu_paged/include/menu_page.hpp>
#include <lib/scene/scenenode.hpp>
#include <lib/include/liblog.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>
#include <lib/resources/ttfont.hpp>

#include <mtypes/include/function.hpp>
#include <mtypes/include/types.hpp>

namespace zoper
{
using namespace lib;
using namespace lib::scene;
using namespace lib::scene::nodes;

void goGame(MenuPaged *scene_node,
            const GameMode game_mode,
            vector<s32> menu_data)
{
    auto &capp = scene_node->app<ZoperProgramController>();
    capp.gameSharedData->startLevel = menu_data[0U];
    capp.gameSharedData->gameMode = game_mode;
    capp.gameSharedData->exitGame = false;
    DisplayLog::info(capp.gameSharedData->to_str());
    scene_node->terminate(1);
}

MainMenu::MainMenu(SceneNode *parent, str name)
    : BaseClass{parent, std::move(name)}
{
    m_gameSharedData = app<ZoperProgramController>().gameSharedData;
}

MainMenu::~MainMenu() = default;

void MainMenu::onCreated()
{
    BaseClass::onCreated();

    auto resources_viewer = dataWrapper<ResourceView>();

    auto normalFont = resources_viewer->getTTFont(MainMenuResources::MenuFontId)->font(72);
#ifdef TEST_BMP_FONT
    auto normalFont = resources_viewer->getBMPFont(MainMenuResources::TestFontId);
#endif

    setNormalTextFont(normalFont);
    setNormalColor(colors::Blue);
    setSelectedColor(colors::Red);

    vector_shared_pointers<scene::MenuPage> menu_steps;

    // Create and register menu pages
    PageOptions main_page_options{true};
    auto menuPageMain(
        createAndConfigureMenuPage(
            "menuPageMain",
            vector_shared_pointers<MenuPagedOption>{
                make_option("Play Token mode", 1),
                make_option("Play Time mode", 2),
                make_option("Options", 3),
                make_option("Exit", MenuPagedOption::GoBack)},
            main_page_options));

    menu_steps.push_back(menuPageMain);

    auto menuPageByToken(
        createAndConfigureMenuPage(
            "menuPageByToken",
            vector_shared_pointers<MenuPagedOption>{
                make_option("Start level Token Mode", 0U, 1U, 10U),
                make_option("Play", MenuPagedOption::Accept),
                make_option("Back", MenuPagedOption::GoBack)}));

    menu_steps.push_back(menuPageByToken);

    menu_steps.back()->Accepted.connect([this](vector<s32> menu_data) {
        goGame(this, GameMode::Token, std::move(menu_data));
    });

    auto menuPageByTime(
        createAndConfigureMenuPage(
            "menuPageByTime",
            vector_shared_pointers<MenuPagedOption>{
                make_option("Start level Time Mode", 0U, 1U, 10U),
                make_option("Play", MenuPagedOption::Accept),
                make_option("Back", MenuPagedOption::GoBack)}));

    menu_steps.push_back(menuPageByTime);

    menu_steps.back()->Accepted.connect([this](vector<s32> menu_data) {
        goGame(this, GameMode::Time, std::move(menu_data));
    });

    auto menuPageOptions(createAndConfigureMenuPage(
        "menuPageOptions",
        vector_shared_pointers<MenuPagedOption>{
            make_option("Antialiasing", 0U,
                        string_vector{"Worst", "Bad", "Normal", "Good", "Best"}),
            make_option("Resolution", 0U,
                        string_vector{"Worst", "Bad", "Normal", "Good", "Best"}),
            make_option("Fullscreen", 0U,
                        string_vector{"No", "Yes"}),
            make_option("VSync", 0U,
                        string_vector{"No", "Yes"}),
            make_option("Redefine keyboard"),
            make_option("Accept", MenuPagedOption::GoBack),
            make_option("Cancel", MenuPagedOption::GoBack)}));

    menu_steps.push_back(menuPageOptions);

    configure_menu(std::move(menu_steps));
}

} // namespace zoper
