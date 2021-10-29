#ifndef HAF_SHAREDDATA_ISHAREABLE_INCLUDE_HPP
#define HAF_SHAREDDATA_ISHAREABLE_INCLUDE_HPP

#include <htypes/include/object.hpp>

namespace haf::data
{
class ISerializable
{
public:
    virtual bool serialize(htps::Object&) const = 0;
    virtual ~ISerializable()                    = default;
};

class IDeserializable
{
public:
    virtual bool deserialize(htps::Object const&) = 0;
    virtual ~IDeserializable()                    = default;
};

class IFullSerializable : public ISerializable, public IDeserializable
{};
}

namespace haf::shdata
{
class IShareable : public data::IFullSerializable
{};

}  // namespace haf::shdata

#endif
