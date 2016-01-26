#ifndef LIB_VERTEXARRAY_HPP
#define LIB_VERTEXARRAY_HPP

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include "idrawable.hpp"
#include <vector>

namespace lib
{
	namespace scn
	{
		namespace draw
		{
			class VertexArray : public IDrawable
			{
			public:

				VertexArray();
				explicit VertexArray(sf::PrimitiveType type, std::size_t vertexCount = 0);

				std::size_t getVertexCount() const;
				sf::Vertex& operator [](std::size_t index);
				const sf::Vertex& operator [](std::size_t index) const;
				void clear();
				void resize(std::size_t vertexCount);
				void append(const sf::Vertex& vertex);
				void setPrimitiveType(sf::PrimitiveType type);
				sf::PrimitiveType getPrimitiveType() const;
				floatRect getBounds() const;
			private:

				virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

				std::vector<sf::Vertex> m_vertices;
				sf::PrimitiveType       m_primitiveType;
			};
		}
	}
}

#endif