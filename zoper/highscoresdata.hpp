#pragma once

#ifndef ZOPER_GAMEDATA_INCLUDE_HPP__
#define ZOPER_GAMEDATA_INCLUDE_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/array.hpp>
#include <mtypes/include/streams.hpp>

namespace zoper
{
	constexpr lib::u32 NumHighScore = 10;

	struct HighScore
	{
		lib::str name{};
		lib::u32 score{ 0 };
	};

	using HighScoreList = lib::array<HighScore, 10>;

	class HighScoreList
	{
	public:

	};

	inline lib::SerializationStreamIn& operator>>(lib::SerializationStreamIn&ssi, HighScore &data)
	{
		ssi >> data.name;
		ssi >> data.score;
		return ssi;
	}

	inline lib::SerializationStreamOut& operator<<(lib::SerializationStreamOut&sso, const HighScore&data)
	{
		sso << data.name;
		sso << data.score;
		return sso;
	}

}

#endif
