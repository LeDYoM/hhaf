export module backend_dev:iresource_info;

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
