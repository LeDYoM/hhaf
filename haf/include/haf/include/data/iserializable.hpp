HTPS_PRAGMA_ONCE
#ifndef HAF_DATA_ISERIALIZABLE_INCLUDE_HPP
#define HAF_DATA_ISERIALIZABLE_INCLUDE_HPP

#include <mc_serial/include/object.hpp>

namespace haf::data
{
class ISerializable
{
public:
    virtual bool serialize(mcs::Object&) const = 0;
    virtual ~ISerializable()                   = default;
};
}  // namespace haf::data

#endif
