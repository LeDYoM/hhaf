#include "gamedata.hpp"

namespace zoper
{
	using namespace lib;

	GameData::GameData() {}
	GameData::~GameData() = default;

	void GameData::generateTokenZones()
	{
		// From left to right
		tokenZones[0].zone = Rectu32{ 0,centerRect.top,centerRect.left - 1, centerRect.bottom() - 1 };
		tokenZones[0].direction = Direction::DirectionData::Right;

		// From top to bottom
		tokenZones[1].zone = Rectu32{ centerRect.left , 0, centerRect.right() - 1, centerRect.top - 1 };
		tokenZones[1].direction = Direction::DirectionData::Down;

		// From right to left
		tokenZones[2].zone = Rectu32{ size.x - 1 , centerRect.top,  centerRect.right(), centerRect.bottom() - 1 };
		tokenZones[2].direction = Direction::DirectionData::Left;

		// From bottom to top
		tokenZones[3].zone = Rectu32{ centerRect.left , size.y - 1, centerRect.right() - 1, centerRect.bottom() - 1 };
		tokenZones[3].direction = Direction::DirectionData::Up;

		for (u32 i = 0; i < NumWays; ++i) {
			tokenZones[i].size = tokenZones[i].direction.isHorizontal() ? centerRect.size().y : centerRect.size().x;
		}
	}
}
