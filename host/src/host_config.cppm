module;

#include <fstream>
#include <string>

export module host:host_config;

import :host_log;

import htypes;
import parpar;
import htypes;

using namespace htps;

namespace
{
static const char kStartApp[] = "StartApp";
}

namespace haf::host
{
export class HostConfig final
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
            HostLogDisplayer::info("Reading config file ", config_file_name_);
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
            HostLogDisplayer::debug("Config file ", config_file_name_,
                                    " not found");
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
                HostLogDisplayer::debug(
                    "Parameter ", kConfigFileParameter,
                    " found with value: ", config_file_name_);
            }
            else
            {
                HostLogDisplayer::debug("Config file: ", config_file_name_);
            }

            HostLogDisplayer::debug("Loading config file ", config_file_name_,
                                    "...");
            loadConfigFile();
        }
    }

private:
    parpar::ParametersParser params_;
    PureDictionary config_data_;
    str config_file_name_{"host_config.cfg"};  ///< Default config file name
    str start_app_{"Zoper"};
};

}  // namespace haf::host
