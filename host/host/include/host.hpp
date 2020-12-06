#ifndef HAF_HOST_MAIN_INCLUDE_HPP
#define HAF_HOST_MAIN_INCLUDE_HPP

#include <mtypes/include/types.hpp>

namespace mtps
{
class str;
}

namespace haf
{
class IApp;
}

/**
 * @brief Class containing a Host from the haf framework.
 */
namespace haf::host
{

class Host final
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

    bool loadApplication(mtps::str const& app_name);
    bool unloadApplication(mtps::str const& app_name);

    /**
     * @brief Main loop function. When it returns, you can safely destroy
     * the Host object.
     * @return int 
     */
    int run();

private:
    class HostPrivate;
    mtps::uptr<HostPrivate> p_;
};
}  // namespace haf::host

#endif
