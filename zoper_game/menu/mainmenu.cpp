#include "mainmenu.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../gameshareddata.hpp"
#include <menu_paged/include/menu_page.hpp>
#include <haf/include/scene/scene_node.hpp>
#include <hlog/include/hlog.hpp>
#include <haf/include/resources/iresource_retriever.hpp>
#include <haf/include/resources/ittfont.hpp>
#include <haf/include/shareddata/ishared_data.hpp>
#include <haf/include/scene_components/iscene_metrics_view.hpp>
#include <htypes/include/function.hpp>
#include <htypes/include/types.hpp>
#include <haf/include/system/datawrappercreator.hpp>

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

void goGame(rptr<MenuPaged> scene_node,
            const GameMode game_mode,
            vector<s32> menu_data)
{
    {
        using namespace haf::shdata;
        auto game_shared_data_updater{SharedDataUpdater<GameSharedData>{
            scene_node->subSystem<ISharedData>()}};

        auto game_shared_data{
            game_shared_data_updater.updateOrCreate(GameSharedData::address())};

        game_shared_data->startLevel = menu_data[0U];
        game_shared_data->gameMode   = game_mode;
        DisplayLog::info(game_shared_data->to_str());
    }

    auto game_shared_data2 = shdata::SharedDataViewer<GameSharedData>(
                                scene_node->subSystem<shdata::ISharedData>())
                                .view(GameSharedData::address());

    auto a = game_shared_data2->score;
    (void)(a);
    scene_node->terminate(MenuFinishedStatus::Forward);
}

void MainMenu::onCreated()
{
    BaseClass::onCreated();

    Rectf32 textBox{
        rectFromSize(subSystem<ISceneMetricsView>()->currentView().size())
            .setLeftTop({0, 750})
            .setSize({2000, 4 * 150})};
    prop<Position>() = textBox.leftTop();

    prop<MenuPagedProperties>()
        .put<NormalTextFont>(
#ifdef TEST_BMP_FONT
            getBMPFont(MainMenuResources::TestFontId)
#else
            subSystem<res::IResourceRetriever>()
                ->getTTFont(MainMenuResources::MenuFontId)
                ->font(72)
#endif
                )
        .put<NormalColor>(colors::Blue)
        .put<SelectedColor>(colors::Red)
        .put<SceneNodeSizeForPages>(textBox.size());

    vector_shared_pointers<scene::MenuPage> menu_steps;

    // Create and register menu pages
    PageOptions main_page_options{true};
    auto menuPageMain{createAndConfigureMenuPage(
        "menuPageMain",
        vector_shared_pointers<MenuPagedOption>{
            make_option("Play Token mode", RangeOption(), 1),
            make_option("Play Time mode", RangeOption(), 2),
            make_option("Options", RangeOption(), 3),
            make_option("Exit", RangeOption(), MenuPagedOption::GoBack)},
        main_page_options)};

    menu_steps.emplace_back(menuPageMain);

    auto menuPageByToken{createAndConfigureMenuPage(
        "menuPageByToken",
        vector_shared_pointers<MenuPagedOption>{
            make_option("Start level Token Mode", RangeOption(1U, 10U)),
            make_option("Play", RangeOption(), MenuPagedOption::Accept),
            make_option("Back", RangeOption(), MenuPagedOption::GoBack)})};

    menu_steps.emplace_back(menuPageByToken);

    menu_steps.back()->Accepted.connect([this](vector<s32> menu_data) {
        goGame(this, GameMode::Token, std::move(menu_data));
    });

    auto menuPageByTime{createAndConfigureMenuPage(
        "menuPageByTime",
        vector_shared_pointers<MenuPagedOption>{
            make_option("Start level Time Mode", RangeOption(1U, 10U)),
            make_option("Play", RangeOption(), MenuPagedOption::Accept),
            make_option("Back", RangeOption(), MenuPagedOption::GoBack)})};

    menu_steps.emplace_back(menuPageByTime);

    menu_steps.back()->Accepted.connect([this](vector<s32> menu_data) {
        goGame(this, GameMode::Time, std::move(menu_data));
    });

    auto menuPageOptions{createAndConfigureMenuPage(
        "menuPageOptions",
        vector_shared_pointers<MenuPagedOption>{
            make_option("Antialiasing", RangeOption{Antialiasing{}}),
            make_option("Resolution",
                        RangeOption(string_vector{"Worst", "Bad", "Normal",
                                                  "Good", "Best"})),
            make_option("Fullscreen", RangeOption(string_vector{"No", "Yes"})),
            make_option("VSync", RangeOption(string_vector{"No", "Yes"})),
            make_option("Redefine keyboard", RangeOption()),
            make_option("Accept", RangeOption(), MenuPagedOption::GoBack),
            make_option("Cancel", RangeOption(), MenuPagedOption::GoBack)})};

    menu_steps.emplace_back(menuPageOptions);

    configure_menu(std::move(menu_steps));

    prop<FinishSceneAtEnd>() = true;
}

}  // namespace zoper
