#include "host_config.hpp"

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
HostConfig::HostConfig(int const argc, char const* const argv[]) :
    params_{parpar::create(argc, argv)}
{}

str const& HostConfig::configuredFirstApp() const
{
    return start_app_;
}

void HostConfig::loadConfigFile()
{
    std::ifstream config_file{config_file_name_.c_str()};
    if (config_file)
    {
        logger::DisplayLog::info("Reading config file ", config_file_name_);
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
        logger::DisplayLog::debug("Config file ", config_file_name_,
                                  " not found");
    }
}

void HostConfig::processCommandLineArguments()
{
    static constexpr char kConfigFileParameter[] = "cfile";

    // First step, check and load the config file
    {
        auto const start_file = params_.optionValue(kConfigFileParameter);

        if (start_file.first)
        {
            config_file_name_ = start_file.second;
            logger::DisplayLog::debug("Parameter ", kConfigFileParameter,
                                      " found with value: ", config_file_name_);
        }
        else
        {
            logger::DisplayLog::debug("Config file: ", config_file_name_);
        }

        logger::DisplayLog::debug("Loading config file ", config_file_name_,
                                  "...");
        loadConfigFile();
    }
}

}  // namespace haf::host
