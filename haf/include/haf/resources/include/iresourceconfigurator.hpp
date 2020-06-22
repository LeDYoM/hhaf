#pragma once

#ifndef HAF_RESOURCES_IRESOURCESCONFIGURATOR_INCLUDE_HPP
#define HAF_RESOURCES_IRESOURCESCONFIGURATOR_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace haf::res
{
class IResourcesConfigurator
{
public:
    virtual bool setResourceConfigFile(mtps::str) = 0;
    virtual bool loadSection(mtps::str const&)    = 0;
};
}  // namespace haf::res

#endif
