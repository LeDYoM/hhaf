#ifndef __LIB_IAPP_HPP__
#define __LIB_IAPP_HPP__

#include "compconfig.hpp"
#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib
{
	namespace scene
	{
		class Scene;
	}
	struct WindowCreationParams
	{
		const str windowTitle;
		u32 width{ 1024 };
		u32 height{ 768 };
		u32 bpp{ 16 };
		u32 antialiasing{ 0 };
		bool vsync{ false };
		bool fullScreen{ false };
		bool resizable{ false };
	};

	struct IAppDescriptor
	{
		const str Name;
		u32 Version;
		u32 SubVersion;
		u32 Patch;
		const char *const configFile;
		const char *const resourceFile;
		WindowCreationParams wcp;
	};

	class IApp
	{
	public:
		constexpr IApp() = default;
		virtual ~IApp() = default;

		virtual void sceneFinished() {}
		virtual const IAppDescriptor getAppDescriptor() const = 0;
		virtual void onInit() = 0;
		virtual int loop() = 0;


	};
}

#endif
