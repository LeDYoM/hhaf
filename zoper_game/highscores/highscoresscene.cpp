#include "highscoresscene.hpp"
#include "highscoresdata.hpp"
#include "highscoretextcontroller.hpp"
#include "highscoresscenestates.hpp"

#include "../loaders/highscoresresources.hpp"

#include <lib/scene/renderizables/renderizable.hpp>
#include <lib/scene/components/renderizables.hpp>
#include <lib/system/resourcemanager.hpp>
#include <lib/core/host.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::scene::nodes;

	void HighScoresScene::onCreated()
	{
		BaseClass::onCreated();

        auto statesController( ensureComponentOfType<StatesController<HighScoresSceneStates>>());
        loadResources(HighScoresResources{});

        m_normalFont = sceneManager().systemProvider().resourceManager().getFont("menu.mainFont")->font(72);
		m_normalColor = colors::Blue;
		m_selectedColor = colors::Red;

        auto renderizables = ensureComponentOfType<Renderizables>();
		m_background = renderizables->createNode("background");
        m_background->figType.set(FigType_t::Quad);
        m_background->pointCount.set(4U);
		m_background->box = rectFromSize(2000.0f, 2000.0f);
        m_background->setTextureFill(sceneManager().systemProvider().resourceManager().getTexture(HighScoresResources::BackgroundTextureId));
		m_background->color = colors::White;

        auto highScoreTextController(createSceneNode<HighScoreTextController>("HighScoreTextController"));
        highScoreTextController->Finished.connect([this,statesController]()
		{
			sceneManager().sceneController()->terminateScene();
		});

		statesController->start(HighScoresSceneStates::Show);
	}

	void HighScoresScene::updateScene()
	{
	}
}
