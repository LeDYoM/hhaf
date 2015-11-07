#include "player.hpp"
#include "lib/scn/draw/ellipseshape.hpp"

#include "gamescene.hpp"

namespace zoper
{
	Player::Player(const lib::vector2du32 &bPosition, const lib::vector2df &size, const lib::Rect &centerRect)
		:lib::board::ITile{ PLAYER_TOKEN }, 
		lib::scn::draw::Renderizable{ "player", new lib::scn::draw::EllipseShape },
		_centerRect( centerRect ), playerDirection{ Direction::Up }
	{
		auto this_ = getAsEllipseShape();
		this_->setPointCount(3);
		this_->setFillColor(sf::Color::White);
		this_->setSize(size);

		setBoardPosition(bPosition);
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
				move(dir);
				return true;
			}
		}
		return false;
	}

	bool Player::onKeyReleased(sf::Event::KeyEvent kEvent)
	{
		return false;
	}

	bool Player::move(const Direction & d)
	{
		__ASSERT(d.isValid(), "Invalid direction passed to move");
		auto dVector = d.DirectionVector();
		auto nPosition = lib::vector2ds32(_boardPosition.x, _boardPosition.y) + lib::vector2ds32(dVector.x, dVector.y);
		if (_centerRect.inBounds(nPosition))
		{
			setBoardPosition(lib::vector2du32(nPosition.x,nPosition.y));
		}
		return false;
	}

	void Player::updateGraphicalDirection()
	{
//		this->getAsEllipseShape()->setRotation();
	}
}
