#ifndef __PLAYER_HPP__
#define __PLAYER_HPP__

#include "lib/board/itilescontroller.hpp"
#include "lib/scn/draw/renderizable.hpp"

namespace zoper
{
	class Player : public lib::board::ITile, public lib::scn::draw::Renderizable
	{
	public:
		Player(lib::u32 x,lib::u32 y);
		virtual ~Player();

		void setBoardPosition(lib::u32 x, lib::u32 y);
		inline lib::u32 boardX() const { return _x; }
		inline lib::u32 boardY() const { return _y; }
	private:
		lib::u32 _x, _y;
	};
}

#endif
