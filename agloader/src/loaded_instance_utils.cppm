module;

#include <string>

export module agloader:utils;

namespace agl
{
std::string formatFileName(std::string fileName,
                           char const* const param_extension,
                           char const* const param_prefix)
{
    if (!fileName.ends_with(param_extension))
    {
        fileName += param_extension;
    }

    return param_prefix + fileName;
}

}  // namespace agl
