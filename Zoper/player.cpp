#include "player.hpp"

namespace zoper
{
	Player::Player()
		: lib::scn::draw::Renderizable{"player", new sf::CircleShape}
	{
	}


	Player::~Player()
	{
	}
}
