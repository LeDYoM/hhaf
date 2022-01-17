#ifndef HAF_BACKEND_DEV_IRESOURCE_INFO_INCLUDE_HPP
#define HAF_BACKEND_DEV_IRESOURCE_INFO_INCLUDE_HPP

#include <htypes/include/str.hpp>

namespace haf::backend
{
class IResourceInfo
{
public:
    virtual htps::str info() const = 0;
    virtual ~IResourceInfo() {}
};
}  // namespace haf::backend

#endif
