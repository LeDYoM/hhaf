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
		class Renderizable : public core::HasName, public IDrawable, public Transformable
		{
		public:
			explicit Renderizable(const std::string &name, sf::PrimitiveType type, std::size_t vertexCount = 0);
			virtual ~Renderizable();

			virtual void draw(sf::RenderStates &states) override;
			virtual void setColor(const sf::Color &color) = 0;

			virtual Rectf32 getLocalBounds() const;
			virtual Rectf32 getGlobalBounds() const;

		protected:
			sf::VertexArray m_vertices;
			Rectf32 m_bounds;
		};
	}
}

#endif
