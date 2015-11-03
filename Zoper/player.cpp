#include "player.hpp"
#include "lib/scn/draw/ellipseshape.hpp"

#include "gamescene.hpp"

namespace zoper
{
	Player::Player(lib::u32 x, lib::u32 y)
		:lib::board::ITile{ PLAYER_TOKEN }, lib::scn::draw::Renderizable{ "player", new lib::scn::draw::EllipseShape }
	{
		this->getAsEllipseShape()->setPointCount(3);
		this->getAsEllipseShape()->setFillColor(sf::Color::White);
		setBoardPosition(x, y);
	}

	Player::~Player()
	{
	}
	void Player::setBoardPosition(lib::u32 x, lib::u32 y)
	{
		_x = x;
		_y = y;
	}
}
