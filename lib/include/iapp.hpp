#ifndef __LIB_IAPP_HPP__
#define __LIB_IAPP_HPP__

#include "compconfig.hpp"
#include "types.hpp"
#include <vector>

// TO Delete:
#include <lib/draw/scene.hpp>

namespace lib
{
	struct WindowCreationParams
	{
		const char *const windowTitle;
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
		const char *const Name;
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

		virtual const IAppDescriptor getAppDescriptor() const = 0;
		virtual void onInit() = 0;
		virtual lib::vector_shared_pointers<draw::Scene> scenesVector() = 0;
		virtual int loop() = 0;


	};
}

#endif
