#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "lib/scn/draw/renderizable.hpp"

namespace zoper
{
	class Player : public lib::scn::draw::Renderizable
	{
	public:
		Player();
		virtual ~Player();
	};
}

#endif
