#ifndef __DIRECTION_HPP__
#define __DIRECTION_HPP__

#include "lib/types.hpp"

namespace zoper
{
	class Direction
	{
	public:
		enum DirectionData : lib::u8
		{
			Left = 0,
			Right = 1,
			Up = 2,
			Down = 3,
			Invalid = 4
		};
		Direction() { data = DirectionData::Up; }
		Direction(DirectionData d) : data{ d } {}
		Direction(lib::u8 d) : data{ (DirectionData)(d) } {}
		Direction(const Direction &other) { data = other.data; }
		Direction &operator=(const Direction &other) { data = other.data; return *this; }
		Direction(Direction &&other) { data = std::move(other.data); }
		Direction &operator=(Direction &&other) { data = std::move(other.data); return *this; }
		operator lib::u8() const { return data; }

		DirectionData value() const { return data; }
		bool isValid() const { return data <= Invalid; }
		static const lib::u8 Total = DirectionData::Invalid;
	private:
		DirectionData data;
	};
}

#endif
