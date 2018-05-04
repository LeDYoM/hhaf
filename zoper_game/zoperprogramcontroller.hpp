#pragma once

#ifndef LIB_ZOPERPROGRAMCONTROLLER_HPP__
#define LIB_ZOPERPROGRAMCONTROLLER_HPP__

#include <lib/include/iapp.hpp>

namespace zoper
{
	using namespace lib;
	class GameSharedData;
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
		virtual IAppDescriptor getAppDescriptor() const override;
		virtual int loop() override;

		sptr<GameSharedData> gameSharedData;
		uptr<KeyMapping> keyMapping;
	};
}

#endif