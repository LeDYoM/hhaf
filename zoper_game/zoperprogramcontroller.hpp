#pragma once

#ifndef LIB_ZOPERPROGRAMCONTROLLER_HPP
#define LIB_ZOPERPROGRAMCONTROLLER_HPP

#include <lib/include/iapp.hpp>

namespace zoper
{
	using namespace lib;
	struct GameSharedData;
	class KeyMapping;
	class MenuScene;
	class GameScene;
	class HighScoresScene;
	class ZoperProgramController : public IApp
	{
	public:
		ZoperProgramController();
		virtual ~ZoperProgramController();

		void onInit() override;
		IAppDescriptor getAppDescriptor() const override;

		sptr<GameSharedData> gameSharedData;
		uptr<KeyMapping> keyMapping;
	};
}

#endif