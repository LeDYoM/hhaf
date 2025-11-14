#ifndef LOADER_LOADEDINSTANCE_PRIVATE_HPP
#define LOADER_LOADEDINSTANCE_PRIVATE_HPP

#include <map>
#include <string>

namespace agloader
{
class LoadedInstancePrivate
{
public:
    void* shared_file_handle{nullptr};
    std::map<std::string, void*> methods_;
};
}

#endif
