#ifndef HAF_HOST_CONFIG_INCLUDE_HPP
#define HAF_HOST_CONFIG_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/dictionary.hpp>
#include <parpar/include/parpar.hpp>

namespace haf::host
{
class HostConfig final
{
public:
    HostConfig(int const argc, char const* const argv[]);
    htps::str const& configuredFirstApp() const;
    void loadConfigFile();
    void processCommandLineArguments();

private:
    parpar::ParametersParser params_;
    htps::PureDictionary config_data_;
    htps::str config_file_name_{
        "host_config.cfg"};  ///< Default config file name
    htps::str start_app_{"HafLife"};
};

}  // namespace haf::host

#endif
