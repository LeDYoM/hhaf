module;

#include "host_export.hpp"
#include <exception>
#include <hosted_app/include/iapp.hpp>

export module host:host;

import :host_log;
import :host_internal;

import htypes;

namespace haf::host
{
/**
 * @brief Class containing a Host from the haf framework.
 */
class HOST_PRIVATE Host final
{
public:
    /**
     * @brief Construct a new Host object. It is recommended to pass the
     * command line parameters in the constructor.
     * @param argc Number of command line parameters.
     * @param argv Pointers to the command line parameters.
     */
    Host(int const argc, char const* argv[]) :
        m_internal{muptr<HostInternal>(argc, argv)}
    {
        DisplayLog::info("Starting HostController...");
        DisplayLog::info("Host version: ", host_VERSION, ".", host_SUBVERSION,
                         ".", host_PATCH, ".", host_TWEAK);
    }

    /**
     * @brief Destroy the Host object
     */
    ~Host()
    {
        DisplayLog::info("Terminating Host...");
        DisplayLog::verbose_if(!m_internal->app_group_.empty(),
                               m_internal->app_group_.size(),
                               " pending apps to be terminated");

        [[maybe_unused]] auto const result{m_internal->unloadAllApplications()};

        DisplayLog::info(result ? "All applications unloaded successfully"
                                : "Problem unloading some applications");
    }

    bool initialize() { return m_internal->initialize(); }

    /**
     * @brief Main loop function. When it returns, you can safely destroy
     * the Host object.
     * @return int
     */
    int run()
    {
        try
        {
            while (!m_internal->exit)
            {
                m_internal->exit = m_internal->update();
            }

            return 0;
        }
        catch (const std::exception& e)
        {
            DisplayLog::error(e.what());
        }
        catch (...)
        {
            DisplayLog::error("Unknown object thrown");
        }
        return 1;
    }

private:
    htps::uptr<HostInternal> m_internal;
};
}  // namespace haf::host
