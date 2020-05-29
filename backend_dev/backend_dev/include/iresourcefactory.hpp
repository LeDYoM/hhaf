#pragma once

#ifndef HAF_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP
#define HAF_BACKEND_IRESOURCE_FACTORY_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/rawmemory.hpp>

namespace haf::backend
{
template <typename T>
class IResourceFactory
{
public:
    virtual T* loadFromFile(const mtps::str&) = 0;
    virtual T* loadFromRawMemory(mtps::RawMemory*) { return nullptr; }
    virtual ~IResourceFactory() {}
};
}  // namespace haf::backend

#endif
