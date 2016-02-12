#include "hostcontroller.hpp"
#include "window.hpp"
#include "log.hpp"
#include "hosttask.hpp"
#include "appcontroller.hpp"

namespace lib
{
	namespace core
	{

		HostController::HostController(const std::vector<std::string> &params)
			: Configuration{ "host.cfg" }
		{
			params;
			LOG_CONSTRUCT_NOPARAMS;
			LOG_INFO("Starting HostController...");
		}

		HostController::~HostController()
		{
			LOG_DESTRUCT_NOPARAMS;
		}

		int HostController::run()
		{
			while (!exit)
			{
				processTask();
				exit = m_apps.empty();
				for (auto app : m_apps)
				{
					bool terminated = app->update();
					if (terminated)
					{
						removeApp(app);
					}
				}
			}

			if (m_apps.empty())
			{
				LOG_INFO("Apps list is empty. Exiting normally");
			}
			return 0;
		}

		void HostController::addApp(uptr<IApp> iapp)
		{
			addTask(sptr<HostTaskLoadAppFromIApp>(new HostTaskLoadAppFromIApp(std::move(iapp))));
		}

		void HostController::removeApp(sptr<AppController> iapp)
		{
			addTask(sptr<HostTaskUnloadApp>(new HostTaskUnloadApp(iapp)));
		}

		void HostController::addTask(sptr<HostTask> newTask)
		{
			m_pendingTasks.push(newTask);
		}

		void HostController::processTask()
		{
			if (!m_pendingTasks.empty())
			{
				auto task = m_pendingTasks.front();
				switch (task->code())
				{
				case HostTask::HostTaskCode::LoadAppFromFileName:
					break;
				case HostTask::HostTaskCode::LoadAppFromIApp:
				{
					sptr<AppController> app = sptr<AppController>(new AppController
						(std::move(std::dynamic_pointer_cast<HostTaskLoadAppFromIApp>(task)->deAttach())));
					m_apps.push_back(app);
				}
				break;
				case HostTask::HostTaskCode::UnloadApp:
				{
					sptr<AppController> app{ std::dynamic_pointer_cast<HostTaskUnloadApp>(task)->deAttach() };
					bool found{ removeFromspVector(app, m_apps) };
					if (found)
					{
						LOG_DEBUG("Going to uninstatiate " << app->appId());
						app.reset();
					}
					else
					{
						LOG_WARNING("Trying to unload unregistered app");
					}
				}
				break;
				default:
					break;
				}
				m_pendingTasks.pop();
			}
		}

	}
}