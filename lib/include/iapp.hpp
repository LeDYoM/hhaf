#ifndef __LIB_IAPP_HPP__
#define __LIB_IAPP_HPP__

#include "compconfig.hpp"
#include "types.hpp"
#include <string>
#include <vector>

// TO Delete:
#include <lib/draw/scene.hpp>

namespace lib
{
	struct WindowCreationParams
	{
		std::string windowTitle;
		u32 width{ 1024 };
		u32 height{ 768 };
		u32 bpp{ 16 };
		u32 antialiasing{ 0 };
		bool vsync{ false };
		bool fullScreen{ false };
		bool resizable{ false };
		inline WindowCreationParams(std::string wt, const u32 w, const u32 h, const u32 b, const u32 aa, const bool vs, const bool fs, const bool rs)
			: windowTitle( std::move(wt) ), width{ w }, height{ h }, bpp{ b }, antialiasing{ aa }, vsync{ vs }, fullScreen{ fs }, resizable{ rs } {}
	};

	struct IAppDescriptor
	{
		std::string Name;
		u32 Version;
		u32 SubVersion;
		u32 Patch;
		std::string configFile;
		std::string resourceFile;
		WindowCreationParams wcp;
		inline IAppDescriptor(std::string n, const u32 v, const u32 s, const u32 p, const std::string &cf, const std::string &rf, const WindowCreationParams &wcp_)
			: Name(std::move(n)), Version{ v }, SubVersion{ s }, Patch{ p }, configFile(cf), resourceFile(rf), wcp(wcp_) {	}
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
