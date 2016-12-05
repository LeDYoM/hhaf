#ifndef __LIB_IDRAWABLE_HPP__
#define __LIB_IDRAWABLE_HPP__

#include <lib/include/types.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace lib
{
	namespace core
	{
		class Window;
	}
	namespace draw
	{
		class IDrawable
		{
		public:
			IDrawable() = default;
			virtual ~IDrawable() = default;

			/*
			virtual bool canDraw() = 0;
			virtual void draw()
			{
				if (isVisible() && canDraw())
				{

				}
			}

			*/
			virtual void draw() = 0;

			inline bool isVisible() const noexcept { return m_visible; }
			inline void setVisible(bool nv) noexcept { m_visible = nv; }
		protected:
			bool m_visible{ true };
		};
	}
}

#endif
