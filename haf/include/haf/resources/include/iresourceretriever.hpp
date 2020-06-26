#pragma once

#ifndef HAF_IRESOURCERETRIVER_INCLUDE_HPP
#define HAF_IRESOURCERETRIVER_INCLUDE_HPP

#include <mtypes/include/str.hpp>
#include <mtypes/include/types.hpp>

namespace haf::res
{
class IFont;
class ITTFont;
class ITexture;
class IShader;

class IResourceRetriever
{
public:
    virtual ~IResourceRetriever() noexcept {}
    virtual mtps::sptr<ITTFont> getTTFont(const mtps::str& rid)   = 0;
    virtual mtps::sptr<ITexture> getTexture(const mtps::str& rid) = 0;
    virtual mtps::sptr<IShader> getShader(const mtps::str& rid)   = 0;
    virtual mtps::sptr<IFont> getBMPFont(const mtps::str& rid)    = 0;
};
}  // namespace haf::res

#endif
