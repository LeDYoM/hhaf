export module haf:data:iserializable;

import :core;

namespace haf::data
{
class ISerializable
{
public:
    virtual bool serialize(mcs::Object&) const = 0;
    virtual ~ISerializable()                   = default;
};
}  // namespace haf::data
