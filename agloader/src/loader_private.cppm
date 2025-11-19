module;

#include "loadedinstance.hpp"
#include <string>
#include <map>
#include <memory>

module agloader;

namespace agloader
{
struct Loader::LoaderPrivate
{
    std::map<std::string, std::shared_ptr<LoadedInstance>> m_loaded_instances;
};

}  // namespace agloader
