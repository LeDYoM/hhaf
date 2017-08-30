#ifndef __LIB_ZOPERPROGRAMCONTROLLER_HPP__
#define __LIB_ZOPERPROGRAMCONTROLLER_HPP__

#include <lib/include/iapp.hpp>

namespace zoper
{
	class GameData;
	class KeyMapping;
	class ZoperProgramController : public lib::IApp
	{
	public:
		ZoperProgramController();
		virtual ~ZoperProgramController();

		void onInit() override;
		void sceneFinished() {};
		virtual const lib::IAppDescriptor getAppDescriptor() const override;
		virtual int loop() override;

		lib::sptr<GameData> gameData;
		lib::uptr<KeyMapping> keyMapping;
	};
}

#endif