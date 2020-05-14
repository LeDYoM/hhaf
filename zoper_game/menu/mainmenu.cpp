#include "mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../gameshareddata.hpp"
#include <menu_paged/include/menu_page.hpp>
#include <haf/scene/include/scenenode.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/resources/include/resourceview.hpp>
#include <haf/resources/include/ittfont.hpp>
#include <haf/shareddata/include/shareddataview.hpp>
#include <haf/scene_components/include/scenemetricsview.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/types.hpp>

using namespace mtps;
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

constexpr auto to_str(Antialiasing aa)
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

void goGame(MenuPaged *scene_node,
            const GameMode game_mode,
            vector<s32> menu_data)
{
    {
        auto game_shared_data_view = scene_node->dataWrapper<shdata::SharedDataView>();
        auto& game_shared_data = game_shared_data_view->dataAs<GameSharedData>();

        game_shared_data.startLevel = menu_data[0U];
        game_shared_data.gameMode = game_mode;
        DisplayLog::info(game_shared_data.to_str());
    }

    scene_node->terminate(1);
}

MainMenu::MainMenu(SceneNode *parent, str name)
    : BaseClass{parent, std::move(name)}
{
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

    Rectf32 textBox{
        rectFromSize(dataWrapper<SceneMetricsView>()->currentView().size())
            .setLeftTop({0, 750})
            .setSize({2000, 4 * 150})};
    position = textBox.leftTop();
    setSceneNodeSizeForPages(textBox.size());

    vector_shared_pointers<scene::MenuPage> menu_steps;

    // Create and register menu pages
    PageOptions main_page_options{true};
    auto menuPageMain(
        createAndConfigureMenuPage(
            "menuPageMain",
            vector_shared_pointers<MenuPagedOption>{
                make_option("Play Token mode", RangeOption(), 1),
                make_option("Play Time mode", RangeOption(), 2),
                make_option("Options", RangeOption(), 3),
                make_option("Exit", RangeOption(), MenuPagedOption::GoBack)},
            main_page_options));

    menu_steps.push_back(menuPageMain);

    auto menuPageByToken(
        createAndConfigureMenuPage(
            "menuPageByToken",
            vector_shared_pointers<MenuPagedOption>{
                make_option("Start level Token Mode", RangeOption(1U, 10U)),
                make_option("Play", RangeOption(), MenuPagedOption::Accept),
                make_option("Back", RangeOption(), MenuPagedOption::GoBack)}));

    menu_steps.push_back(menuPageByToken);

    menu_steps.back()->Accepted.connect([this](vector<s32> menu_data) {
        goGame(this, GameMode::Token, std::move(menu_data));
    });

    auto menuPageByTime(
        createAndConfigureMenuPage(
            "menuPageByTime",
            vector_shared_pointers<MenuPagedOption>{
                make_option("Start level Time Mode", RangeOption(1U, 10U)),
                make_option("Play", RangeOption(), MenuPagedOption::Accept),
                make_option("Back", RangeOption(), MenuPagedOption::GoBack)}));

    menu_steps.push_back(menuPageByTime);

    menu_steps.back()->Accepted.connect([this](vector<s32> menu_data) {
        goGame(this, GameMode::Time, std::move(menu_data));
    });

    auto menuPageOptions(createAndConfigureMenuPage(
        "menuPageOptions",
        vector_shared_pointers<MenuPagedOption>{
            make_option("Antialiasing", RangeOption{Antialiasing{}}),
            make_option("Resolution", RangeOption(string_vector{"Worst", "Bad", "Normal", "Good", "Best"})),
            make_option("Fullscreen", RangeOption(string_vector{"No", "Yes"})),
            make_option("VSync", RangeOption(string_vector{"No", "Yes"})),
            make_option("Redefine keyboard", RangeOption()),
            make_option("Accept", RangeOption(), MenuPagedOption::GoBack),
            make_option("Cancel", RangeOption(), MenuPagedOption::GoBack)}));

    menu_steps.push_back(menuPageOptions);

    configure_menu(std::move(menu_steps));
}

} // namespace zoper
