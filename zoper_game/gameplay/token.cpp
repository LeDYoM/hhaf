#include "token.hpp"

#include <lib/scene/renderizables/nodeshape.hpp>
#include <lib/scene/ianimation.hpp>
#include <lib/scene/components/animationcomponent.hpp>

#include <lib/include/core/log.hpp>

#include "gamescene.hpp"
#include "levelproperties.hpp"

namespace zoper
{
	using namespace lib;
	using namespace lib::scene;
	using namespace lib::board;

	u32 Token::m_tileCounter{ 0 };

	Token::Token(SceneNode* const parent, str name, BoardTileData data, const Rectf32 &box) :
		GameBaseTile{ parent, name + str(m_tileCounter) + str(m_tileCounter), data }
	{
		++m_tileCounter;
		m_node = createRenderizable<nodes::NodeShape>("Node", 30);
		m_node->box = box;
		m_node->color = getColorForToken();
	}

	Token::~Token() = default;

	void Token::resetTileCounter()
	{
		m_tileCounter = 0;
	}

    void Token::tileAdded(const vector2dst & position_)
    {
        log_debug_info("Token ", name(), " appeared at ", position_);
        // Set the position in the scene depending on the board position
//        setBoardPosition(position);
    }

    void Token::tileRemoved(const vector2dst &position_)
    {
        log_debug_info("Deleting token ", name(), " from scene at position ", position_);
    }

    void Token::tileChanged(const vector2dst &position_, const board::BoardTileData oldValue, const board::BoardTileData newValue)
    {
        log_debug_info("Token at position ", position_, " changed from ", oldValue, " to ", newValue);
        set(newValue);
    }

    void Token::tileMoved(const vector2dst & /*source*/, const vector2dst & dest)
    {
        auto animationComponent(ensureComponentOfType<anim::AnimationComponent>());
        animationComponent->addAnimation(muptr<anim::IPropertyAnimation<vector2df>>
            (
                TimeFromMillis(
                    parentSceneAs<GameScene>()->
                        ensureComponentOfType<LevelProperties>()->millisBetweenTokens() / 2
                ),
                position, position(),
                parentSceneAs<GameScene>()->board2Scene(dest)));
    }
}
