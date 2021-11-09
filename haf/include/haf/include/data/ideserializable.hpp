#ifndef HAF_DATA_IDESERIALIZABLE_INCLUDE_HPP
#define HAF_DATA_IDESERIALIZABLE_INCLUDE_HPP

#include <htypes/include/object.hpp>

namespace haf::data
{
class IDeserializable
{
public:
    virtual bool deserialize(htps::Object const&) = 0;
    virtual ~IDeserializable()                    = default;
};
}

#endif
