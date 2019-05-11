#include "gameover.hpp"

#include "../loaders/gameresources.hpp"

#include <lib/scene/scenemanager.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/nodes/scenenodetext.hpp>

#include <lib/scene/components/alignedtextcomponent.hpp>

#include <logger/include/log.hpp>
#include <lib/include/resources/iresourceretriever.hpp>
#include <lib/resources/ttfont.hpp>

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
    using namespace lib::scene::nodes;

    GameOverSceneNode::GameOverSceneNode(scene::SceneNode * const parent, str name)
        : SceneNode{parent, std::move(name)}
    {
        m_gameOverrg = parent->createSceneNode("gameOverScreen");

        vector2df gosize{ parentScene()->scenePerspective().width, 715 };
        m_gameOverrg->position.set({ 0, 575 });

        auto gameText(m_gameOverrg->createSceneNode<SceneNodeText>("gameovergame"));
        gameText->text.set(Text_t("GAME"));
        gameText->font.set(parentScene()->sceneManager().resources().getFont(GameResources::ScoreFontId)->font(360));
        gameText->textColor.set(FillColor_t{ colors::White });
        {
            auto align(gameText->ensureComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(gosize);
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Top);
        }

        auto overText(m_gameOverrg->createSceneNode<SceneNodeText>("gameoverover"));
        overText->text.set(Text_t("OVER"));
        overText->font.set(parentScene()->sceneManager().resources().getFont(GameResources::ScoreFontId)->font(360));
        overText->textColor.set(FillColor_t{ colors::White });
        {
            auto align(overText->ensureComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(gosize);
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Bottom);
        }

        m_gameOverrg->visible = false;
    }

    GameOverSceneNode::~GameOverSceneNode() = default;
}
