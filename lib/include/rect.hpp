#ifndef LIB_RECT_INCLUDE_HPP__
#define LIB_RECT_INCLUDE_HPP__

#include "types.hpp"
#include <lib/include/vector2d.hpp>

namespace lib
{
	template <typename T>
	struct Rect
	{
		T left, top, width, height;

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
			const T minX = std::min(left, static_cast<T>(left + width));
			const T maxX = std::max(left, static_cast<T>(left + width));
			const T minY = std::min(top, static_cast<T>(top + height));
			const T maxY = std::max(top, static_cast<T>(top + height));

			return (x >= minX) && (x < maxX) && (y >= minY) && (y < maxY);
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

		inline constexpr bool intersects(const Rect<T>& rectangle) const noexcept
		{
			return intersects(rectangle, std::move(Rect<T>()));
		}

		inline constexpr bool operator==(const Rect &r) const noexcept
		{
			return (left == r.left && width == r.width && top == r.top && height == r.height);
		}

		inline constexpr bool operator!=(const Rect<T> &r) const noexcept
		{
			return !(operator==(r));
		}

		inline void setLeftTop(const vector2d<T>&nleftTop) { setLeft(nleftTop.x); setTop(nleftTop.y); }
		inline void move(const vector2d<T>&relativePosition) { left += relativePosition.x; top += relativePosition.y; }
		inline void setSize(const vector2d<T>&nsize) { width = nsize.x; height = nsize.y; }

		inline vector2d<T> leftTop() const { return vector2d<T>{left, top}; }
		inline vector2d<T> size() const { return vector2d<T>{width, height}; }
		inline T right() const { return left + width; }
		inline T bottom() const { return top + height; }
		inline vector2d<T> rightBottom() const { return vector2d<T>{right(), bottom()}; }
		inline vector2d<T> rightTop() const { return vector2d<T>{right(), top}; }
		inline vector2d<T> leftBottom() const { return vector2d<T>{left, bottom()}; }
	};

	using Rects32 = lib::Rect<s32>;
	using Rectf32 = lib::Rect<f32>;
	using Rectu32 = lib::Rect<u32>;

}

#endif
