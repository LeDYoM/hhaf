#include "tile.hpp"
#include <SFML/Graphics.hpp>

namespace zoper
{
	Tile::Tile(lib::board::BoardTileData data) : lib::board::ITile{ data }, lib::draw::Renderizable("",new sf::CircleShape)
	{
	}
	Tile::~Tile()
	{
	}
}
