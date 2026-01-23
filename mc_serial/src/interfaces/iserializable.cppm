export module mc_serial:iserializable;

import :object;

namespace mcs
{
class ISerializable
{
public:
    virtual bool serialize(mcs::Object&) const = 0;
    virtual ~ISerializable()                   = default;
};
}  // namespace mcs
