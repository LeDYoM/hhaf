#include "gamescenedata.hpp"
#include "gamescene.hpp"

#include "../loaders/gameresources.hpp"

#include <lib/scene/nodes/scenenodetext.hpp>
#include <lib/scene/components/alignedtextcomponent.hpp>

#include <lib/resources/texture.hpp>
#include <lib/resources/ttfont.hpp>

#include <lib/core/host.hpp>
#include <lib/system/resourcemanager.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;
    using namespace lib::scene::nodes;

    void GameSceneData::createData(GameScene &gameScene, const GameMode gameMode)
    {
        gameScene.loadResources(GameResources{});

        m_levelrg = gameScene.createSceneNode("level");
        m_pauseSceneNode = gameScene.createSceneNode("pause");

        m_pauseText = m_pauseSceneNode->createSceneNode<SceneNodeText>("pausetext");
        m_pauseText->text.set(Text_t("PAUSE"));
        m_pauseText->font.set(gameScene.parentScene()->sceneManager().resources().getFont(GameResources::ScoreFontId)->font(180));
        m_pauseText->textColor.set(FillColor_t{colors::White});
        {
            auto align(m_pauseText->ensureComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(gameScene.scenePerspective().size());
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Middle);
        }

        m_levelrg->position = vector2df{ 1250, 50 };

        m_pauseSceneNode->visible = false;
    }
}
