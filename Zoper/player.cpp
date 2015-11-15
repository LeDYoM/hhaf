#include "player.hpp"
#include "lib/scn/draw/ellipseshape.hpp"

#include "gamescene.hpp"

namespace zoper
{
	Player::Player(const lib::vector2du32 &bPosition, const lib::vector2df &size)
		:lib::board::ITile{ PLAYER_TOKEN }, 
		lib::scn::draw::Renderizable{ "player", new lib::scn::draw::EllipseShape },
		playerDirection{ Direction::Up }
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

	void Player::setCurrentDirection(const Direction & direction)
	{
		playerDirection = direction;
		auto this_ = getAsEllipseShape();
//		this_->setRotation(playerDirection.angle());
	}

	void Player::updateGraphicalDirection()
	{
//		this->getAsEllipseShape()->setRotation();
	}
}
