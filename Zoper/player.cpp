#include "player.hpp"
#include "lib/scn/draw/ellipseshape.hpp"

#include "gamescene.hpp"

namespace zoper
{
	Player::Player(const lib::vector2du32 &bPosition, const sf::Vector2f &size)
		:lib::board::ITile{ PLAYER_TOKEN }, lib::scn::draw::Renderizable{ "player", new lib::scn::draw::EllipseShape }
	{
		auto this_ = getAsEllipseShape();
		this_->setPointCount(3);
		this_->setFillColor(sf::Color::White);
		this_->setSize(size);

		setBoardPosition(bPosition);
		playerDirection = Direction::Up;
	}

	Player::~Player()
	{
	}

	void Player::setBoardPosition(const lib::vector2du32 &np)
	{
		_boardPosition = np;
	}

	bool Player::onKeyPressed(sf::Event::KeyEvent kEvent)
	{
		auto dir = getDirectionFromKey(kEvent.code);
		if (dir.isValid())
		{
			if (dir != playerDirection)
			{
				playerDirection = dir;
			}
		}
		return false;
	}
	bool Player::onKeyReleased(sf::Event::KeyEvent kEvent)
	{
		return false;
	}

	void Player::updateGraphicalDirection()
	{
//		this->getAsEllipseShape()->setRotation();
	}
}
