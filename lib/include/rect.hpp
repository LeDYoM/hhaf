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

		static constexpr Rect fromSize(T sizeX, T sizeY) { return Rect{ {},{}, vector2d<T>{sizeX,sizeY} }; }
		static constexpr Rect fromSize(const vector2d<T> &size) { return Rect{ {},{}, size }; }
		static constexpr Rect fromCenterAndRadius(const vector2d<T> &center, const vector2d<T> &radius) { return Rect{ center.x - radius.x,center.y - radius.y, center.x + radius.x, center.y + radius.y }; }
		static constexpr Rect fromCenterAndSize(const vector2d<T> &center, const vector2d<T> &size) { return fromCenterAndRadius(center, size * static_cast<T>(2)); }

		constexpr Rect(T rectLeft, T rectTop, T rectWidth, T rectHeight) noexcept : left{ rectLeft }, top{ rectTop }, width{ rectWidth }, height{ rectHeight } { }
		constexpr Rect() = default;
		constexpr Rect(vector2d<T> position, vector2d<T> size) noexcept : Rect{ position.x, position.y, size.x, size.y } {}
		constexpr Rect(vector2d<T> position, T sizeX, T sizeY) noexcept : Rect{ position.x, position.y, sizeX, sizeY } {}
		constexpr Rect(T positionX, T positionY, vector2d<T> size) noexcept : Rect{ positionX, positionY, size.x, size.y } {}

		constexpr Rect(const Rect&) noexcept = default;
		Rect &operator=(const Rect&) noexcept = default;
		constexpr Rect(Rect&&) noexcept = default;
		Rect &operator=(Rect&&) noexcept = default;
		template <typename U>
		constexpr Rect(const Rect<U>& rectangle) :
			left{ static_cast<T>(rectangle.left) }, top{ static_cast<T>(rectangle.top) },
			width{ static_cast<T>(rectangle.width) }, height{ static_cast<T>(rectangle.height) } {}

		constexpr vector2d<T> center() const { return vector2d<T> {left + (width / static_cast<T>(2)), 
			top + (height / static_cast<T>(2))}; }

		constexpr const bool operator==(const Rect &r) const
		{
			return (left == r.left && width == r.width && top == r.top && height == r.height);
		}

		constexpr const bool operator!=(const Rect &r) const
		{
			return !(operator==(r));
		}

		constexpr Rect& operator +=(const vector2d<T> &rhs)
		{
			left += rhs.x;
			top += rhs.y;
			return *this;
		}

		constexpr Rect& operator +=(const Rect &rhs)
		{
			left += rhs.left;
			top += rhs.top;
			return *this;
		}

		constexpr Rect& move(const Rect &rhs)
		{
			return (*this) += rhs;
		}

		constexpr void setLeftTop(const vector2d<T>&nleftTop) { left = nleftTop.x; top = nleftTop.y; }
		constexpr void move(const vector2d<T>&relativePosition)  { left += relativePosition.x; top += relativePosition.y; }
		constexpr void setSize(const vector2d<T>&nsize) { width = nsize.x; height = nsize.y; }
		constexpr void setRadiusFromCenter(const vector2d<T> &radius) {
			auto c(center());
			left = static_cast<T>(c.x - radius.x);
			top = static_cast<T>(c.y - radius.y);
			width = static_cast<T>(radius.x * static_cast<T>(2));
			height = static_cast<T>(radius.x * static_cast<T>(2));
		}

		constexpr const vector2d<T> leftTop() const noexcept { return vector2d<T>{left, top}; }
		constexpr const vector2d<T> size() const  noexcept { return vector2d<T>{width, height}; }
		constexpr const T right() const  noexcept { return left + width; }
		constexpr const T bottom() const  noexcept { return top + height; }
		constexpr const vector2d<T> rightBottom() const noexcept { return vector2d<T>{right(), bottom()}; }
		constexpr const vector2d<T> rightTop() const  noexcept { return vector2d<T>{right(), top}; }
		constexpr const vector2d<T> leftBottom() const  noexcept { return vector2d<T>{left, bottom()}; }

		constexpr const Rect move(const vector2d<T> &offset) const { return (Rect( *this ) += offset); };
		constexpr const Rect resize(const vector2d<T> &sSize) const { return Rect{ left, top, width + sSize.x, height + sSize.y }; };
		constexpr const Rect setRadiusFromCenter(const vector2d<T> &radius) const { Rect temp{ *this }; temp.setRadiusFromCenter(radius); return temp; }
	};

	// Serialization operators
	template <typename T>
	constexpr write_stream& operator<<(write_stream & os, const Rect<T> &rect)
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
