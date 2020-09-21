#pragma once

#ifndef HAF_SHAREDDATA_ISHAREABLE_INCLUDE_HPP
#define HAF_SHAREDDATA_ISHAREABLE_INCLUDE_HPP

#include <mtypes/include/object.hpp>

namespace haf::shdata
{
class IShareable
{
public:
    virtual ~IShareable() {}
    virtual bool serialize(mtps::Object&) const = 0;
    virtual bool deserialize(mtps::Object const&) const = 0;  
};

}  // namespace haf::shdata

#endif
