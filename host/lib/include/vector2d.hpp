#ifndef LIB_VECTOR2D_INCLUDE_HPP
#define LIB_VECTOR2D_INCLUDE_HPP

#include "types.hpp"

namespace lib
{
	template <typename T>
	class vector2d
	{
	public:
		constexpr inline vector2d()  noexcept : x{}, y{} {}
		constexpr inline vector2d(T X, T Y)  noexcept : x{ X }, y{ Y } {}
		constexpr inline vector2d(const vector2d<T> &) = default;
		inline vector2d &operator=(const vector2d<T> &) = default;

		template <typename U>
		constexpr inline explicit vector2d(const vector2d<U>& vector)  noexcept : x{ static_cast<T>(vector.x) }, y{ static_cast<T>(vector.y) } {}

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

		inline constexpr vector2d operator+(const vector2d &right) const noexcept { return (vector2d(*this) += right); }
		inline constexpr vector2d operator-(const vector2d &right) const noexcept { return (vector2d(*this) -= right); }
		inline constexpr vector2d operator*(const vector2d &right) const noexcept { return (vector2d(*this) *= right); }
		inline constexpr vector2d operator/(const vector2d &right) const noexcept { return (vector2d(*this) /= right); }
		inline constexpr vector2d operator*(const T &right) const noexcept { return (vector2d(*this) *= right);	}
		inline constexpr vector2d operator/(const T &right) const noexcept { return (vector2d(*this) /= right); }
		inline constexpr bool operator ==(const vector2d &right) const noexcept { return (x == right.x && y == right.y); }
		inline constexpr bool operator !=(const vector2d &right) const noexcept {	return !(*operator==(right)); }

		T x;
		T y;
	};

	// Serialization operators
	template <typename T>
	inline std::ostream& operator<<(std::ostream & os, const vector2d<T> &v2d)
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
