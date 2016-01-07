#include "incrementscoreToken.hpp"

namespace zoper
{
	IncrementScoreToken::IncrementScoreToken(const lib::u32 score)
		: lib::scn::draw::Renderizable{ "", new sf::Text }, _score{ score }
	{
	}


	IncrementScoreToken::~IncrementScoreToken()
	{
	}
}
