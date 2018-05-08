#include "player.hpp"
#include "constants.hpp"

#include <mtypes/include/log.hpp>

#include <lib/scene/ianimation.hpp>
#include <lib/scene/components/animationcomponent.hpp>

namespace zoper
{
    using namespace lib;
    using namespace lib::scene;

    Player::Player(SceneNode* const parent, const str& name, vector2dst bPosition, Rectf32 box, vector2df board2SceneFactor)
        : GameBaseTile{ parent, name, 0 },
        boardPosition{ std::move(bPosition),
            [this]() {
                log_debug_info("Player board position: ",boardPosition());
                position = vector2df{ m_board2SceneFactor.x * boardPosition().x, m_board2SceneFactor.y * boardPosition().y };
                log_debug_info("Player scene position: ",position());
            }
        },
        currentDirection( Direction(Direction::DirectionData::Up) ), m_board2SceneFactor{ std::move(board2SceneFactor) }
    {
        m_extraSceneNode = createSceneNode("m_extraSceneNode");
        m_extraSceneNode_2 = m_extraSceneNode->createSceneNode("m_extraSceneNode_2");
        m_node = m_extraSceneNode_2->createRenderizable<nodes::NodeShape>("Node", 3);

        m_node->box = std::move(box);
        m_node->color = getColorForToken();
    }

    Player::~Player() = default;

    void Player::movePlayer(const Direction & direction, const function<bool(const vector2dst&)> &pointInCenter, const sptr<board::BoardModelComponent>& boardModel)
    {
        CLIENT_ASSERT(direction.isValid(), "Invalid direction passed to move");
        currentDirection = direction;
        auto nPosition = direction.applyToVector(boardPosition());
        if (pointInCenter(nPosition)) {
            boardModel->moveTile(boardPosition(), nPosition);
            boardPosition.set(nPosition);
        }
        else {
            updateDirection();
        }
    }

    void Player::updateDirection()
    {
        updateDirectionFromParameter(currentDirection());
    }

    void Player::updateDirectionFromParameter(const Direction destDirection)
    {
        const auto tileCenter(m_board2SceneFactor / 2.0f);
        m_extraSceneNode->rotateAround(tileCenter, destDirection.angle());

        if (destDirection.value() == Direction::DirectionData::Up ||
            destDirection.value() == Direction::DirectionData::Down) {
            m_extraSceneNode_2->scaleAround(tileCenter, { 1, 1 });
        }
        else {
            m_extraSceneNode_2->scaleAround(tileCenter, { m_board2SceneFactor.y / m_board2SceneFactor.x, m_board2SceneFactor.x / m_board2SceneFactor.y });
        }
    }

    void Player::launchAnimation(vector2df toWhere)
    {
        auto currentPosition(position());

        auto animationComponent(ensureComponentOfType<anim::AnimationComponent>());
        animationComponent->
            addAnimation(muptr<anim::IPropertyAnimation<vector2df>>(
                TimeFromMillis(gameplay::constants::MillisAnimationLaunchPlayerStep),
                position, 
                position(), toWhere,
                [this,currentPosition = std::move(currentPosition)]() { launchAnimationBack(currentPosition); }
            ));
    }

    void Player::launchAnimationBack(vector2df toWhere)
    {
        updateDirectionFromParameter(currentDirection().negate());
        auto animationComponent(ensureComponentOfType<anim::AnimationComponent>());
        animationComponent->
            addAnimation(muptr<anim::IPropertyAnimation<vector2df>>(
                TimeFromMillis(gameplay::constants::MillisAnimationLaunchPlayerStep),
                position,
                position(), toWhere,
                [this]() { updateDirection(); }
                
            ));
    }
}
