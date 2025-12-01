#ifndef HAF_BACKEND_DEV_IRESOURCE_INFO_INCLUDE_HPP
#define HAF_BACKEND_DEV_IRESOURCE_INFO_INCLUDE_HPP

import htypes;

namespace haf::backend
{
class IResourceInfo
{
protected:
    virtual ~IResourceInfo() = default;

public:
    virtual htps::str info() const = 0;
};
}  // namespace haf::backend

#endif
