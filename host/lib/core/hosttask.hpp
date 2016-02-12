#ifndef __HOSTTASK_HPP__
#define __HOSTTASK_HPP__

#include <string>
#include <lib/include/iapp.hpp>

namespace lib
{
	namespace core
	{
		class HostTask
		{
		public:
			enum class HostTaskCode
			{
				LoadAppFromFileName,
				LoadAppFromIApp,
				UnloadApp
			};
			const HostTaskCode code() const { return m_hostTaskCode; }
			virtual ~HostTask() {}
		protected:
			HostTask(const HostTaskCode hostTaskCode) : m_hostTaskCode(hostTaskCode) {}
		private:
			HostTaskCode m_hostTaskCode;
		};

		class HostTaskLoadAppFromFileName : public HostTask
		{
		public:
			HostTaskLoadAppFromFileName(const std::string &fileName) : HostTask( HostTaskCode::LoadAppFromFileName ), m_fileName(fileName) {}
		private:
			std::string m_fileName;
		};

		class HostTaskLoadAppFromIApp : public HostTask
		{
		public:
			HostTaskLoadAppFromIApp(uptr<IApp> app) : HostTask( HostTaskCode::LoadAppFromIApp ), m_app(std::move(app)) {}
			uptr<IApp> deAttach() { return std::move(m_app); }
		private:
			uptr<IApp> m_app;
		};

		class HostTaskUnloadApp : public HostTask
		{
		public:
			HostTaskUnloadApp(sptr<AppController> app) : HostTask(HostTaskCode::UnloadApp), m_app{ app } {}
			sptr<AppController> deAttach() { return std::move(m_app); }
		private:
			sptr<AppController> m_app;
		};

	}
}
#endif
