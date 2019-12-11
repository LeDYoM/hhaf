#include "menuscene.hpp"
#include <lib/scene/components/renderizables.hpp>
#include <lib/scene/datawrappers/resourceview.hpp>
#include <lib/resources/texture.hpp>
#include <lib/system/resourcemanager.hpp>

#include "../menu/mainmenu.hpp"
#include "../gameshareddata.hpp"
#include "../loaders/mainmenuresources.hpp"
#include "../zoperprogramcontroller.hpp"

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;

    constexpr u32 PointsPerQuad = 6U;

    void MenuScene::onCreated()
    {
        BaseClass::onCreated();

        loadResources(MainMenuResources{});
        auto renderizables = addComponentOfType<Renderizables>();
        auto resources_viewer = dataWrapper<ResourceView>();
    
        auto background = renderizables->createNode("background");
        background->figType.set(FigType_t::Quad);
        background->pointCount.set(PointsPerQuad);
        background->box = rectFromSize(2000.0f, 2000.0f);
        background->color = colors::White;
        background->color_modifier = [](const RenderizableModifierContext&context)
        {
            const auto n = context.normalizedVertexInBox();
            static constexpr auto decrease_ratio = 0.5F;
            return Color::fromFloats(
                n.y * decrease_ratio,
                n.y * decrease_ratio,
                n.y * decrease_ratio);
        };

        auto logo = renderizables->createNode("mainLogo");
        logo->figType.set(FigType_t::Quad);
        logo->pointCount.set(PointsPerQuad);
        logo->box = Rectf32{ 500, 150, 1000, 500 };
        logo->setTextureFill(resources_viewer->getTexture(MainMenuResources::LogoId));
        logo->color = colors::White;

        auto mainMenu (createSceneNode<MainMenu>(MainMenu::ClassName));
        mainMenu->MenuFinished.connect([this]()
        {
            app<ZoperProgramController>().gameSharedData->exitGame = true;
            sceneManager().sceneController()->terminateScene();
        });
    }
}
