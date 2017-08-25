#ifndef ZOPER_GAMECONFIG_HPP__
#define ZOPER_GAMECONFIG_HPP__

#include <lib/core/configuration.hpp>
#include <lib/core/iuserproperties.hpp>

namespace zoper
{
	class GameConfig : public lib::IUserProperties
	{
	public:
		GameConfig();
		virtual ~GameConfig();

		void setProperties(lib::Configuration &config) override;

		lib::s32 gameMode;
		lib::u32 startLevel;
		lib::u32 score;
	};
}

#endif