#include "menuscene.hpp"
#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/renderizables/nodequad.hpp>
#include <lib/core/resourcemanager.hpp>
#include <lib/core/host.hpp>
#include <lib/core/debugsystem.hpp>

#include "../menu/mainmenu.hpp"
#include "../common.hpp"
#include "../gameshareddata.hpp"
#include "../loaders/mainmenuresources.hpp"

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;
    using namespace lib::scene::nodes;

    MenuScene::MenuScene() : BaseClass{ "MenuScene" } {}

    void MenuScene::onCreated()
    {
        BaseClass::onCreated();

        loadResources(MainMenuResources{});
        m_background = createRenderizable<NodeQuad>("background");
        m_background->box = rectFromSize(2000.0f, 2000.0f);
        m_background->setTextureFill(sceneManager().host().resourceManager().getTexture(MainMenuResources::BackgroundTextureId));
        m_background->color = colors::White;

        m_logo = createRenderizable<NodeQuad>("mainLogo");
        m_logo->box = Rectf32{ 500, 150, 1000, 500 };
        m_logo->setTextureFill(sceneManager().host().resourceManager().getTexture(MainMenuResources::LogoId));
        m_logo->color = colors::White;

        auto mainMenu (createSceneNode<MainMenu>(MainMenu::ClassName));
        mainMenu->MenuFinished.connect([this]() {
            zApp().gameSharedData->exitGame = true;
            sceneManager().terminateScene();
        });
    }
}
