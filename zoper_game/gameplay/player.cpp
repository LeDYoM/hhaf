#include "player.hpp"
#include "constants.hpp"
#include "tokenzones.hpp"

#include <logger/include/log.hpp>

#include <lib/scene/ianimation.hpp>
#include <lib/scene/components/animationcomponent.hpp>
#include <lib/scene/components/renderizables.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;

    Player::Player(SceneNode* const parent, const str& name, vector2dst bPosition, Rectf32 box, vector2df board2SceneFactor)
          :	GameBaseTile{ parent, name, 0 },
	        boardPosition{ std::move(bPosition),
	            [this]() 
                {
		            log_debug_info("Player board position: ", boardPosition());
	                position = vector2df{ m_board2SceneFactor.x * boardPosition().x, m_board2SceneFactor.y * boardPosition().y };
	                log_debug_info("Player scene position: ", position());
	            }
		    },
		currentDirection{ Direction{Direction::DirectionData::Up} }, m_board2SceneFactor{ std::move(board2SceneFactor) }
    {
        m_extraSceneNode = createSceneNode("m_extraSceneNode");
        m_extraSceneNode_2 = m_extraSceneNode->createSceneNode("m_extraSceneNode_2");
        
        auto renderizables = m_extraSceneNode_2->ensureComponentOfType<Renderizables>();
        m_node = renderizables->createNode("Node");
        m_node->figType.set(FigType_t::Shape);
        m_node->pointCount.set(3U);

        m_node->box.set(box);
        m_node->color.set(getColorForToken());
        updateDirectionFromParameter(currentDirection());
    }

	Player::~Player() {}

    void Player::movePlayer(const Direction & direction, const sptr<board::BoardModelComponent>& boardModel)
    {
        assert_debug(direction.isValid(), "Invalid direction passed to move");
        currentDirection = direction;
        auto nPosition = direction.applyToVector(boardPosition());
        if (TokenZones::pointInCenter(nPosition)) 
        {
            boardModel->moveTile(boardPosition(), nPosition);
            boardPosition.set(nPosition);
        }
        else
        {
            updateDirectionFromParameter(currentDirection());
        }
    }

    void Player::updateDirectionFromParameter(const Direction destDirection)
    {
        const auto tileCenter(m_board2SceneFactor / 2.0F);
        m_extraSceneNode->rotateAround(tileCenter, destDirection.angle());

		m_extraSceneNode_2->scaleAround(tileCenter, 
			(destDirection.isVertical()) ?
				vector2df{ 1, 1 }:
				vector2df{ m_board2SceneFactor.y / m_board2SceneFactor.x, m_board2SceneFactor.x / m_board2SceneFactor.y }
		);
    }

    void Player::launchAnimation(vector2df toWhere)
    {
        auto currentPosition(position());

        auto animationComponent(ensureComponentOfType<anim::AnimationComponent>());
        animationComponent->
            addAnimation(muptr<anim::IPropertyAnimation<vector2df>>(dataWrapper<scene::Timer>(),
                TimePoint_as_miliseconds(gameplay::constants::MillisAnimationLaunchPlayerStep),
                position, 
                position(), toWhere,
                [this,currentPosition = std::move(currentPosition)]() { launchAnimationBack(currentPosition); }
            ));
    }

    void Player::tileAdded(const vector2dst & position_)
    {
        log_debug_info("TokenPlayer appeared at ", position_);
        // Set the position in the scene depending on the board position
        boardPosition.set(position_);
    }

    void Player::tileChanged(const vector2dst &position_, const board::BoardTileData oldValue, const board::BoardTileData newValue)
    {
        log_debug_info("Player (position ", position_, ") changed from ", oldValue, " to ", newValue);
        set(newValue);
    }

    void Player::tileMoved(const vector2dst &, const vector2dst &)
    {
        updateDirectionFromParameter(currentDirection());
    }

    void Player::launchAnimationBack(vector2df toWhere)
    {
        updateDirectionFromParameter(currentDirection().negate());
        auto animationComponent(ensureComponentOfType<anim::AnimationComponent>());
        animationComponent->
            addAnimation(muptr<anim::IPropertyAnimation<vector2df>>(dataWrapper<scene::Timer>(),
                TimePoint_as_miliseconds(gameplay::constants::MillisAnimationLaunchPlayerStep),
                position,
                position(), toWhere,
                [this]() { updateDirectionFromParameter(currentDirection()); }
        ));
    }
}
