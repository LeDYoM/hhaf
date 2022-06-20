HTPS_PRAGMA_ONCE
#ifndef HAF_DATA_ISERIALIZABLE_INCLUDE_HPP
#define HAF_DATA_ISERIALIZABLE_INCLUDE_HPP

#include <htypes/include/object.hpp>

namespace haf::data
{
class ISerializable
{
public:
    virtual bool serialize(htps::Object&) const = 0;
    virtual ~ISerializable()                    = default;
};
}

#endif
