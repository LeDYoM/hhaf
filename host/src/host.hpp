#ifndef HAF_HOST_MAIN_INCLUDE_HPP
#define HAF_HOST_MAIN_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include "host_export.hpp"

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
    Host(int argc, char* argv[]);

    /**
     * @brief Destroy the Host object
     */
    ~Host();

    bool initialize();

    /**
     * @brief Main loop function. When it returns, you can safely destroy
     * the Host object.
     * @return int
     */
    int run();

private:
    class HostPrivate;
    htps::uptr<HostPrivate> p_;
};
}  // namespace haf::host

#endif
