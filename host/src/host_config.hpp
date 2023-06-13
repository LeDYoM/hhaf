#ifndef HAF_HOST_CONFIG_INCLUDE_HPP
#define HAF_HOST_CONFIG_INCLUDE_HPP

#include <hlog/include/hlog.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/dictionary.hpp>
#include <mc_serial/include/object.hpp>
#include <parpar/include/parpar.hpp>

#include <fstream>
#include <string>

using namespace htps;

namespace
{
static const char kStartApp[] = "StartApp";
}

namespace haf::host
{
class HostConfig final
{
public:
    HostConfig(int const argc, char const* const argv[]) :
        params_{parpar::create(argc, argv)}
    {}

    str const& configuredFirstApp() const { return start_app_; }

    void loadConfigFile()
    {
        std::ifstream config_file{config_file_name_.c_str()};
        if (config_file)
        {
            DisplayLog::info("Reading config file ", config_file_name_);
            std::string key;
            std::string value;
            while (config_file >> key >> value)
            {
                if (key == kStartApp)
                {
                    start_app_ = value.c_str();
                }
            }
        }
        else
        {
            DisplayLog::debug("Config file ", config_file_name_, " not found");
        }
    }

    void processCommandLineArguments()
    {
        static constexpr char kConfigFileParameter[] = "cfile";

        // First step, check and load the config file
        {
            auto const start_file = params_.optionValue(kConfigFileParameter);

            if (start_file.first)
            {
                config_file_name_ = start_file.second;
                DisplayLog::debug("Parameter ", kConfigFileParameter,
                                  " found with value: ", config_file_name_);
            }
            else
            {
                DisplayLog::debug("Config file: ", config_file_name_);
            }

            DisplayLog::debug("Loading config file ", config_file_name_, "...");
            loadConfigFile();
        }
    }

private:
    parpar::ParametersParser params_;
    PureDictionary config_data_;
    str config_file_name_{"host_config.cfg"};  ///< Default config file name
    str start_app_{"HafLife"};
};

}  // namespace haf::host

#endif
