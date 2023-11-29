MCS_PRAGMA_ONCE
#ifndef MCS_ISERIALIZABLE_INCLUDE_HPP
#define MCS_ISERIALIZABLE_INCLUDE_HPP

#include <mc_serial/include/object.hpp>

namespace mcs
{
class ISerializable
{
public:
    virtual bool serialize(mcs::Object&) const = 0;
    virtual ~ISerializable()                   = default;
};
}  // namespace mcs

#endif
