#ifndef __LIB_IAPP_HPP__
#define __LIB_IAPP_HPP__

#include "compconfig.hpp"
#include "types.hpp"
#include <string>
#include <vector>

// TO Delete:
#include <lib/core/vecsptr.hpp>
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
		inline WindowCreationParams(const std::string &wt, const u32 w, const u32 h, const u32 b, const u32 aa, const bool vs, const bool fs, const bool rs)
			: windowTitle( wt ), width{ w }, height{ h }, bpp{ b }, antialiasing{ aa }, vsync{ vs }, fullScreen{ fs }, resizable{ rs } {}
		/*
		inline WindowCreationParams(const WindowCreationParams &rh)
			: windowTitle(rh.windowTitle), width{ rh.width }, height{ rh.height }, bpp{ rh.bpp }, antialiasing{ rh.antialiasing }, 
			vsync{ rh.vsync }, fullScreen{ rh.fullScreen }, resizable{ rh.resizable } {}
			*/
	};

	struct IAppDescriptor
	{
		std::string Name;
		lib::u32 Version;
		lib::u32 SubVersion;
		lib::u32 Patch;
		std::string configFile;
		std::string resourceFile;
		WindowCreationParams wcp;
		inline IAppDescriptor(const std::string &n, const u32 v, const u32 s, const u32 p, const std::string &cf, const std::string &rf, const WindowCreationParams &wcp_)
			: Name(n), Version{ v }, SubVersion{ s }, Patch{ p }, configFile(cf), resourceFile(rf), wcp(wcp_) {	}

		/*
		inline IAppDescriptor(const IAppDescriptor &rh) : Name(rh.Name), Version{ rh.Version }, SubVersion{ rh.SubVersion }, Patch{ rh.Patch }, configFile{ rh.configFile },
			resourceFile{ rh.resourceFile }, wcp{ rh.wcp } {}
			*/
	};

	struct ServicesRequest
	{
		std::vector<std::string> requestedServices;
		ServicesRequest(ServicesRequest &&rh) : requestedServices( std::move(rh.requestedServices) ) {}
		ServicesRequest() {}
	};

	class IApp
	{
	public:
		IApp() {}
		virtual ~IApp() {}

		virtual const IAppDescriptor getAppDescriptor() const = 0;
		virtual ServicesRequest getServicesRequest() const = 0;
		virtual void onInit() = 0;
		virtual lib::VecSPtr<scn::Scene> scenesVector() = 0;
		virtual int loop() = 0;


	};
}

#endif
