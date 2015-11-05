#include "player.hpp"
#include "lib/scn/draw/ellipseshape.hpp"

#include "gamescene.hpp"

namespace zoper
{
	Player::Player(lib::u32 x, lib::u32 y, const sf::Vector2f &size)
		:lib::board::ITile{ PLAYER_TOKEN }, lib::scn::draw::Renderizable{ "player", new lib::scn::draw::EllipseShape }
	{
		auto this_ = getAsEllipseShape();
		this_->setPointCount(3);
		this_->setFillColor(sf::Color::White);
		this_->setSize(size);

		setBoardPosition(x, y);
		playerDirection = Direction::Up;
	}

	Player::~Player()
	{
	}
	void Player::setBoardPosition(lib::u32 x, lib::u32 y)
	{
		_x = x;
		_y = y;
	}
	bool Player::onKeyPressed(sf::Event::KeyEvent kEvent)
	{
		auto dir = getDirectionFromKey(kEvent.code);
		if (dir != Direction::Total)
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
