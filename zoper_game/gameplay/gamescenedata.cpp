#include "gamescenedata.hpp"
#include "gamescene.hpp"

#include <lib/scene/nodes/scenenodetext.hpp>
#include <lib/scene/components/alignedtextcomponent.hpp>

#include <lib/core/host.hpp>
#include <lib/core/resourcemanager.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;
    using namespace lib::scene::nodes;

    void GameSceneData::createData(GameScene &gameScene, const GameMode gameMode)
    {
        m_gameresources.loadResources(resourceManager());

        m_mainBoardrg = gameScene.createSceneNode("mainBoard");
        m_gameOverrg = gameScene.createSceneNode("gameOverScreen");
        m_levelrg = gameScene.createSceneNode("level");
        m_pauseSceneNode = gameScene.createSceneNode("pause");

        m_scoreQuad = gameScene.createSceneNode<TextQuad>("score", 
            resourceManager().getFont(GameResources::ScoreFontId)->font(90), 
            colors::White, vector2df{600, 300});
        m_scoreQuad->position.set(vector2df{ 50, 150 });
        m_scoreQuad->text(vector2dst{0,0})->text.set(Text_t("Level:"));
        m_scoreQuad->text(vector2dst{0,0})->textColor = FillColor_t(colors::Blue);
        m_scoreQuad->text(vector2dst{0,1})->text.set(Text_t("Score:"));
        m_scoreQuad->text(vector2dst{0,1})->textColor = FillColor_t(colors::Blue);

        m_goalQuad = gameScene.createSceneNode<TextQuad>("goal", 
            resourceManager().getFont(GameResources::ScoreFontId)->font(90), 
            colors::White, vector2df{600, 300});
        m_goalQuad->position.set(vector2df{ 1250, 50 });
        m_goalQuad->text(vector2dst{0,0})->textColor = FillColor_t(colors::Blue);
        m_goalQuad->text(vector2dst{0,1})->textColor = FillColor_t(colors::Blue);

        m_pauseText = m_pauseSceneNode->createSceneNode<SceneNodeText>("pausetext");
        m_pauseText->text.set(Text_t("PAUSE"));
        m_pauseText->font.set(resourceManager().getFont(GameResources::ScoreFontId)->font(180));
        m_pauseText->textColor.set(FillColor_t{colors::White});
        {
            auto align(m_pauseText->ensureComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(gameScene.scenePerspective().size());
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Middle);
        }

        vector2df gosize{ gameScene.scenePerspective().width, 715 };
        m_gameOverrg->position.set({0, 575});

        auto gameText(m_gameOverrg->createSceneNode<SceneNodeText>("gameovergame"));
        gameText->text.set(Text_t("GAME"));
        gameText->font.set(resourceManager().getFont(GameResources::ScoreFontId)->font(360));
        gameText->textColor.set(FillColor_t{colors::White});
        {
            auto align(gameText->ensureComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(gosize);
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Top);
        }

        auto overText(m_gameOverrg->createSceneNode<SceneNodeText>("gameoverover"));
        overText->text.set(Text_t("OVER"));
        overText->font.set(resourceManager().getFont(GameResources::ScoreFontId)->font(360));
        overText->textColor.set(FillColor_t{colors::White});
        {
            auto align(overText->ensureComponentOfType<AlignedTextComponent>());
            align->alignmentSize.set(gosize);
            align->alignmentX.set(AlignedTextComponent::AlignmentX::Center);
            align->alignmentY.set(AlignedTextComponent::AlignmentY::Bottom);
        }

        m_levelrg->position = vector2df{ 1250, 50 };

        m_gameOverrg->visible = false;
        m_mainBoardrg->visible = true;
        m_pauseSceneNode->visible = false;

        m_goalQuad->text(vector2dst{0,0})->text.set(Text_t(
                gameMode == GameMode::Token?"Tokens: ":"Time: ")
                );
        m_goalQuad->text(vector2dst{0,1})->text.set(Text_t("Goal: "));
    }
}
