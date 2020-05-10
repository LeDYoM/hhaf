#pragma once

#ifndef HAF_BACKEND_DEV_IRESOURCE_INFO_INCLUDE_HPP
#define HAF_BACKEND_DEV_IRESOURCE_INFO_INCLUDE_HPP

#include <mtypes/include/str.hpp>

namespace haf::backend
{
class IResourceInfo
{
public:
    virtual mtps::str info() const = 0;
    virtual ~IResourceInfo() {}
};
}  // namespace haf::backend

#endif
