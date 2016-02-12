#ifndef __DIRECTION_HPP__
#define __DIRECTION_HPP__

#include <lib/include/types.hpp>
#include <lib/core/log.hpp>

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
		bool isValid() const { return data < Invalid; }

		static const lib::u8 Total = DirectionData::Invalid;

		inline bool isHorizontal() const { return data == DirectionData::Left || data == DirectionData::Right; }

		inline Direction negate() const {
			switch (data)
			{
			case DirectionData::Left:
				return DirectionData::Right;
				break;
			case DirectionData::Right:
				return DirectionData::Left;
				break;
			case DirectionData::Up:
				return DirectionData::Down;
				break;
			case DirectionData::Down:
				return DirectionData::Up;
				break;
			case DirectionData::Invalid:
			default:
				LOG_ERROR("Invalid direction. Cannot convert");
			}
			return DirectionData::Invalid;
		}

		lib::vector2du32 applyToVector(const lib::vector2du32 &v,const lib::u32 scale = 1) const
		{
			lib::vector2ds32 dv{ directionVector(scale) };
			lib::vector2du32 result(v.x + dv.x, v.y + dv.y);
			return result;
		}

		const lib::vector2ds32 directionVector(const lib::u32 scale = 1) const
		{
			lib::vector2ds32 result{ 0,0 };

			switch (data)
			{
			case DirectionData::Left:
				result = lib::vector2ds32(-1, 0);
				break;
			case DirectionData::Right:
				result = lib::vector2ds32(1, 0);
				break;
			case DirectionData::Up:
				result = lib::vector2ds32(0, -1);
				break;
			case DirectionData::Down:
				result = lib::vector2ds32(0, 1);
				break;
			case DirectionData::Invalid:
			default:
				LOG_ERROR("Invalid direction. Cannot convert");
			}

			result *= (lib::s32)scale;
			return result;
		}

		const lib::vector2ds32 negatedDirectionVector(const lib::u32 scale = 1) const
		{
			lib::vector2ds32 result{ directionVector(scale) };
			result *= (lib::s32) - 1;
			return result;
		}

		lib::f32 angle() const
		{
			lib::f32 result{ 0.f };

			switch (data)
			{
			case DirectionData::Left:
				result = 270.f;
				break;
			case DirectionData::Right:
				result = 90.f;
				break;
			case DirectionData::Up:
				result = 0.f;
				break;
			case DirectionData::Down:
				result = 180.f;
				break;
			case DirectionData::Invalid:
			default:
				LOG_ERROR("Invalid direction. Cannot convert");
			}

			return result;
		}

	private:
		DirectionData data;
	};
}

#endif
