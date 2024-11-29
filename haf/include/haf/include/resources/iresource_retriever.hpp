HTPS_PRAGMA_ONCE
#ifndef HAF_RESOURCES_RESOURCE_RETRIVER_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCE_RETRIVER_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

namespace haf::res
{
class IFont;
class ITTFont;
class ITexture;
class IShader;

class IResourceRetriever
{
protected:
    ~IResourceRetriever() = default;

public:
    virtual htps::sptr<ITTFont> getTTFont(htps::str const& rid) const   = 0;
    virtual htps::sptr<ITexture> getTexture(htps::str const& rid) const = 0;
    virtual htps::sptr<IShader> getShader(htps::str const& rid) const   = 0;
    virtual htps::sptr<IFont> getBMPFont(htps::str const& rid) const    = 0;
};

}  // namespace haf::res

#endif
