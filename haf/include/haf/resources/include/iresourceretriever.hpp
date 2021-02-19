#ifndef HAF_IRESOURCERETRIVER_INCLUDE_HPP
#define HAF_IRESOURCERETRIVER_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <htypes/include/types.hpp>

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
    virtual htps::sptr<ITTFont> getTTFont(const htps::str& rid) const   = 0;
    virtual htps::sptr<ITexture> getTexture(const htps::str& rid) const = 0;
    virtual htps::sptr<IShader> getShader(const htps::str& rid) const   = 0;
    virtual htps::sptr<IFont> getBMPFont(const htps::str& rid) const    = 0;
};
}  // namespace haf::res

#endif
