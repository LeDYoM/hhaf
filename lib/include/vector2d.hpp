#ifndef LIB_VECTOR2D_INCLUDE_HPP
#define LIB_VECTOR2D_INCLUDE_HPP

#pragma once

#include "types.hpp"

namespace lib
{
	template <typename T>
	class vector2d
	{
	public:
		constexpr vector2d()  : x{}, y{} {}
		constexpr vector2d(T X, T Y)  : x{ X }, y{ Y } {}
		constexpr vector2d(const vector2d<T> &) = default;
		inline vector2d &operator=(const vector2d<T> &) = default;

		template <typename U>
		constexpr explicit vector2d(const vector2d<U>& vector)  noexcept : x{ static_cast<T>(vector.x) }, y{ static_cast<T>(vector.y) } {}

		inline vector2d &operator+=(const vector2d &right) noexcept
		{
			x += right.x;
			y += right.y;
			return *this;
		}

		inline vector2d &operator-=(const vector2d &right) noexcept
		{
			x -= right.x;
			y -= right.y;
			return *this;
		}

		inline vector2d &operator*=(const vector2d &right) noexcept
		{
			x *= right.x;
			y *= right.y;
			return *this;
		}

		inline vector2d &operator*=(const T &scalar) noexcept
		{
			x *= scalar;
			y *= scalar;
			return *this;
		}

		inline vector2d &operator/=(const vector2d &right)
		{
			x /= right.x;
			y /= right.y;
			return *this;
		}

		inline vector2d &operator/=(const T &scalar)
		{
			x /= scalar;
			y /= scalar;
			return *this;
		}

		inline vector2d &operator-() noexcept
		{
			x = -x;
			y = -y;
			return *this;
		}

		T dotProduct(const vector2d& p2) const noexcept
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

		T x;
		T y;
	};

	template <typename T>
	constexpr vector2d<T> operator-(const vector2d<T> &v2d) noexcept
	{
		return vector2d<T>{-v2d.x, -v2d.y};
	}

	// Serialization operators
	template <typename T>
	inline write_stream& operator<<(write_stream & os, const vector2d<T> &v2d)
	{
		os << "{" << v2d.x << "," << v2d.y << "}";
		return os;
	}

	template <typename T>
	inline std::istream& operator >> (std::istream & is, const vector2d<T> &v2d)
	{
		std::string p;
		is >> p;	// "{"
		is >> v.x;
		is >> p;	// ","
		is >> v.y;
		is >> p;	// "}"
		return is;
	}

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
