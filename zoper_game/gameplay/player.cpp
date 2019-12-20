#include "player.hpp"
#include "constants.hpp"
#include "tokenzones.hpp"

#include <lib/include/liblog.hpp>

#include <lib/scene/components/renderizables.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;

    Player::Player(SceneNode* const parent, str name)
        : BaseClass{ parent, std::move(name) }, boardPosition{ },
        currentDirection{ Direction{Direction::DirectionData::Up} }, m_board2SceneFactor{ }
    {
        m_extraSceneNode = createSceneNode("m_extraSceneNode");
        m_extraSceneNode_2 = m_extraSceneNode->createSceneNode("m_extraSceneNode_2");
        
        auto renderizables = m_extraSceneNode_2->addComponentOfType<Renderizables>();
        m_node = renderizables->createNode("Node");
        m_node->figType.set(FigType_t::Shape);
        m_node->pointCount.set(3U);
        data.set(0);
    }

	Player::~Player() {}

    void Player::setUp(vector2dst bPosition, Rectf32 box, vector2df board2SceneFactor)
    {
        m_board2SceneFactor = board2SceneFactor;
        boardPosition.set(bPosition);
        m_node->box.set(box);
    }

    void Player::update()
    {
        BaseClass::update();

        if (boardPosition.readResetHasChanged())
        {
            DisplayLog::info("Player board position: ", boardPosition());
            position = vector2df{ m_board2SceneFactor.x * boardPosition().x, m_board2SceneFactor.y * boardPosition().y };
            DisplayLog::info("Player scene position: ", position());
        }
    }

    void Player::movePlayer(const Direction & direction, const sptr<board::BoardModelComponent>& boardModel)
    {
        log_assert(direction.isValid(), "Invalid direction passed to move");
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
            (!destDirection.isVertical()) ?
                vector2df{ 1, 1 }:
                vector2df{ m_board2SceneFactor.y / m_board2SceneFactor.x, m_board2SceneFactor.x / m_board2SceneFactor.y }
        );
    }

    void Player::launchAnimation(vector2df toWhere)
    {
        ensureComponentOfType(animation_component_);
        animation_component_->
            addPropertyAnimation(
                TimePoint_as_miliseconds(gameplay::constants::MillisAnimationLaunchPlayerStep),
                position,
                toWhere,
                [this, currentPosition = position()]() { launchAnimationBack(currentPosition); }
            );
    }

    void Player::launchAnimationBack(vector2df toWhere)
    {
        DisplayLog::info("Creating animation for player to go back");
        updateDirectionFromParameter(currentDirection().negate());
        ensureComponentOfType(animation_component_);
        animation_component_->
            addPropertyAnimation(
                TimePoint_as_miliseconds(gameplay::constants::MillisAnimationLaunchPlayerStep),
                position,
                toWhere,
                [this]() { updateDirectionFromParameter(currentDirection()); }
        );
    }

    void Player::tileAdded(const vector2dst & position_)
    {
        DisplayLog::info("TokenPlayer appeared at ", position_);
        m_node->color.set(getColorForToken());
        updateDirectionFromParameter(currentDirection());

        // Set the position in the scene depending on the board position
        boardPosition.set(position_);
    }

    void Player::tileChanged(const vector2dst &position_, const board::BoardTileData oldValue, const board::BoardTileData newValue)
    {
        DisplayLog::info("Player (position ", position_, ") changed from ", oldValue, " to ", newValue);
        data.set(newValue);
    }

    void Player::tileMoved(const vector2dst &, const vector2dst &)
    {
        updateDirectionFromParameter(currentDirection());
    }
}
