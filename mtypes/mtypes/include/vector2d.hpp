#pragma once

#ifndef LIB_VECTOR2D_INCLUDE_HPP
#define LIB_VECTOR2D_INCLUDE_HPP

#include "types.hpp"
#include "types_ext.hpp"

namespace lib
{
	template <typename T>
	class vector2d
	{
	public:
		constexpr vector2d &operator+=(const vector2d &right) noexcept
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		constexpr vector2d &operator-=(const vector2d &right) noexcept
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		constexpr vector2d &operator*=(const vector2d &right) noexcept
		{
			x *= right.x;
			y *= right.y;
			return *this;
		}

		constexpr vector2d &operator*=(const T &scalar) noexcept
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		constexpr vector2d &operator/=(const vector2d &right)
		{
			x /= right.x;
			y /= right.y;
			return *this;
		}

		constexpr vector2d &operator/=(const T &scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		constexpr vector2d &operator-() noexcept
		{
			x = -x;
			y = -y;
			return *this;
		}

		constexpr T dotProduct(const vector2d& p2) const noexcept
		{
			auto r(*this * p2);
			return r.x + r.y;
		}

		// Compute the normal of a segment
		vector2d computeNormal( const vector2d& p2) const noexcept
		{
			vector2d<T> normal{ *this - p2 };
			T length (static_cast<T>(std::sqrt(normal.x * normal.x + normal.y * normal.y)));
			if (length != T{})
				normal /= length;
			return normal;
		}

		constexpr vector2d operator+(const vector2d &right) const noexcept { return (vector2d(*this) += right); }
		constexpr vector2d operator-(const vector2d &right) const noexcept { return (vector2d(*this) -= right); }
		constexpr vector2d operator*(const vector2d &right) const noexcept { return (vector2d(*this) *= right); }
		constexpr vector2d operator/(const vector2d &right) const noexcept { return (vector2d(*this) /= right); }
		constexpr vector2d operator*(const T &right) const noexcept { return (vector2d(*this) *= right);	}
		constexpr vector2d operator/(const T &right) const noexcept { return (vector2d(*this) /= right); }
		constexpr bool operator ==(const vector2d &right) const noexcept { return (x == right.x && y == right.y); }
		constexpr bool operator !=(const vector2d &right) const noexcept {	return !(*operator==(right)); }

		// Conversion operator
		template <typename Y>
		constexpr explicit operator vector2d<Y>() const noexcept { return vector2d<Y>{static_cast<Y>(x), static_cast<Y>(y) }; }

		T x;
		T y;
	};

	template <typename T>
	constexpr vector2d<T> operator/(const vector2d<T> &lhs, const vector2d<T> &rhs) noexcept
	{
		return lhs / rhs;
	}

	template <typename T>
	constexpr vector2d<T> operator-(const vector2d<T> &v2d) noexcept
	{
		return vector2d<T>{-v2d.x, -v2d.y};
	}

	// Serialization operators
	template <typename T>
	constexpr write_stream& operator<<(write_stream & os, const vector2d<T> &v2d)
	{
		os << "{" << v2d.x << "," << v2d.y << "}";
		return os;
	}

	template <typename T>
	inline std::istream& operator >> (read_stream & is, const vector2d<T> &v2d)
	{
//		str p;
//		is >> p;	// "{"
//		is >> v.x;
//		is >> p;	// ","
//		is >> v.y;
//		is >> p;	// "}"
		return is;
	}

	static_assert(std::is_pod_v < vector2d<u8> >, "vector2d is not a pod");

	using vector2du8 = vector2d<u8>;
	using vector2ds8 = vector2d<s8>;
	using vector2du16 = vector2d<u16>;
	using vector2ds16 = vector2d<s16>;
	using vector2du32 = vector2d<u32>;
	using vector2ds32 = vector2d<s32>;
	using vector2df = vector2d<f32>;
	using vector2dd = vector2d<f64>;
}

#endif
