#ifndef __LIB_RENDERIZABLE_HPP__
#define __LIB_RENDERIZABLE_HPP__

#include "hasname.hpp"
#include "idrawable.hpp"
#include "transformable.hpp"
#include <lib/include/types.hpp>
#include <lib/include/vector2d.hpp>
#include <SFML/Graphics.hpp>

namespace lib
{
	namespace draw
	{
		enum class Alignment : u8
		{
			Left = 0,
			Center = 1,
			Right = 2
		};

		class Renderizable : public lib::core::HasName, public IDrawable, public Transformable
		{
		public:
			explicit Renderizable(const std::string &name);
			virtual ~Renderizable();

			virtual u32 draw(sf::RenderStates &states) override;
			virtual void setColor(const sf::Color &color) = 0;

			virtual sf::FloatRect getLocalBounds() const = 0;
			virtual sf::FloatRect getGlobalBounds() const = 0;

			// Some useful shortcuts
			using Transformable::setPosition;
			void setPosition(const vector2df &pos, Alignment alignment);
			void setPositionX(const float x, Alignment alignment = Alignment::Left);
			void setPositionY(const float y, Alignment alignment = Alignment::Left);
			void setAlignment(Alignment alignment);
		};
	}
}

#endif
