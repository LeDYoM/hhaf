#ifndef LIB_RECT_INCLUDE_HPP__
#define LIB_RECT_INCLUDE_HPP__

#pragma once

#include "types.hpp"
#include <lib/include/vector2d.hpp>

namespace lib
{
	template <typename T>
	struct Rect
	{
		T left, top, width, height;

		static inline Rect fromSize(T sizeX, T sizeY) { return Rect{ {},{}, std::forward<vector2d<T>>({sizeX,sizeY}) }; }
		static inline Rect fromSize(const vector2d<T> &size) { return Rect{ {},{}, size }; }
		static inline Rect fromCenterAndRadius(const vector2d<T> &center, const vector2d<T> &radius) { return Rect{ center.x - radius.x,center.y - radius.y, center.x + radius.x, center.y + radius.y }; }
		static inline Rect fromCenterAndSize(const vector2d<T> &center, const vector2d<T> &size) { return fromCenterAndRadius(center, size * static_cast<T>(2)); }

		inline constexpr Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight) noexcept : left{ rectLeft }, top{ rectTop }, width{ rectWidth }, height{ rectHeight } { }
		inline constexpr Rect() noexcept : Rect{ {}, {}, {}, {} } {}
		inline constexpr Rect(vector2d<T> position, vector2d<T> size) noexcept : Rect{ position.x, position.y, size.x, size.y } {}
		inline constexpr Rect(vector2d<T> position, T sizeX, T sizeY) noexcept : Rect{ position.x, position.y, sizeX, sizeY } {}
		inline constexpr Rect(T positionX, T positionY, vector2d<T> size) noexcept : Rect{ positionX, positionY, size.x, size.y } {}

		inline constexpr Rect(const Rect&) noexcept = default;
		inline Rect &operator=(const Rect&) noexcept = default;
		inline constexpr Rect(Rect&&) noexcept = default;
		inline Rect &operator=(Rect&&) noexcept = default;
		template <typename U>
		inline constexpr Rect(const Rect<U>& rectangle) :
			left{ static_cast<T>(rectangle.left) }, top{ static_cast<T>(rectangle.top) },
			width{ static_cast<T>(rectangle.width) }, height{ static_cast<T>(rectangle.height) } {}

		inline constexpr vector2d<T> center() const { return vector2d<T> {left + (width / static_cast<T>(2)), 
			top + (height / static_cast<T>(2))}; }

		inline constexpr bool contains(const T x, const T y) const noexcept
		{
			return ((x >= std::min(left, static_cast<T>(left + width)))
				&& (x < std::max(left, static_cast<T>(left + width))) 
				&& (y >= std::min(top, static_cast<T>(top + height)))
				&& (y < std::max(top, static_cast<T>(top + height))));
		}

		inline constexpr bool contains(const vector2d<T>& point) const noexcept
		{
			return contains(point.x, point.y);
		}

		inline constexpr bool intersects(const Rect& rectangle, Rect& intersection) const noexcept
		{
			const T r1MinX = std::min(left, right());
			const T r1MaxX = std::max(left, right());
			const T r1MinY = std::min(top, bottom());
			const T r1MaxY = std::max(top, bottom());

			const T r2MinX = std::min(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
			const T r2MaxX = std::max(rectangle.left, static_cast<T>(rectangle.left + rectangle.width));
			const T r2MinY = std::min(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));
			const T r2MaxY = std::max(rectangle.top, static_cast<T>(rectangle.top + rectangle.height));

			// Compute the intersection boundaries
			const T interLeft = std::max(r1MinX, r2MinX);
			const T interTop = std::max(r1MinY, r2MinY);
			const T interRight = std::min(r1MaxX, r2MaxX);
			const T interBottom = std::min(r1MaxY, r2MaxY);

			// If the intersection is valid (positive non zero area), then there is an intersection
			if ((interLeft < interRight) && (interTop < interBottom)) {
				intersection = Rect{ interLeft, interTop, interRight - interLeft, interBottom - interTop };
				return true;
			}
			else {
				intersection = Rect{};
				return false;
			}
		}

		constexpr inline bool intersects(const Rect<T>& rectangle) const noexcept
		{
			return intersects(rectangle, std::move(Rect<T>()));
		}

		constexpr inline bool operator==(const Rect &r) const noexcept
		{
			return (left == r.left && width == r.width && top == r.top && height == r.height);
		}

		constexpr inline bool operator!=(const Rect &r) const noexcept
		{
			return !(operator==(r));
		}

		constexpr inline Rect& operator +=(const vector2d<T> &rhs) noexcept
		{
			left += rhs.x;
			top += rhs.y;
			return *this;
		}

		constexpr inline Rect& operator +=(const Rect &rhs) noexcept
		{
			left += rhs.left;
			top += rhs.top;
			return *this;
		}

		constexpr inline Rect& move(const Rect &rhs) noexcept
		{
			return (*this) += rhs;
		}

		constexpr inline void setLeftTop(const vector2d<T>&nleftTop) noexcept { left = nleftTop.x; top = nleftTop.y; }
		constexpr inline void move(const vector2d<T>&relativePosition)  noexcept { left += relativePosition.x; top += relativePosition.y; }
		constexpr inline void setSize(const vector2d<T>&nsize) noexcept { width = nsize.x; height = nsize.y; }

		constexpr inline const vector2d<T> leftTop() const noexcept { return vector2d<T>{left, top}; }
		constexpr inline const vector2d<T> size() const  noexcept { return vector2d<T>{width, height}; }
		constexpr inline const T right() const  noexcept { return left + width; }
		constexpr inline const T bottom() const  noexcept { return top + height; }
		constexpr inline const vector2d<T> rightBottom() const noexcept { return vector2d<T>{right(), bottom()}; }
		constexpr inline const vector2d<T> rightTop() const  noexcept { return vector2d<T>{right(), top}; }
		constexpr inline const vector2d<T> leftBottom() const  noexcept { return vector2d<T>{left, bottom()}; }

		constexpr inline const Rect moved(const vector2d<T> &offset) const noexcept { return (Rect( *this ) += offset); };
		constexpr inline const Rect resized(const vector2d<T> &sSize) const noexcept { return Rect{ left, top, width + sSize.x, height + sSize.y }; };
		constexpr inline const Rect resized_from_center(const vector2d<T> &sSize) const noexcept { 
			auto center = center();
			return Rect{ left, top, width + sSize.x, height + sSize.y }; 
		};
	};

	// Serialization operators
	template <typename T>
	constexpr inline write_stream& operator<<(write_stream & os, const Rect<T> &rect)
	{
		os << "{ {" << rect.left << "," << rect.top << "}, {" << rect.width << "," << rect.height << "} }";
		return os;
	}

	using Rectu8 = Rect<u8>;
	using Rects8 = Rect<s8>;
	using Rectu16 = Rect<u16>;
	using Rects16 = Rect<s16>;
	using Rects32 = Rect<s32>;
	using Rectu32 = Rect<u32>;
	using Rectf32 = Rect<f32>;
	using Rectf64 = Rect<f64>;
}

#endif
