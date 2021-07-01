#ifndef HAF_RESOURCES_RESOURCE_RETRIVER_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCE_RETRIVER_INCLUDE_HPP

#include <htypes/include/str.hpp>
#include <htypes/include/types.hpp>
#include <haf/include/system/idatawrapper.hpp>

namespace haf::res
{
class IFont;
class ITTFont;
class ITexture;
class IShader;

class ResourceRetriever : public sys::IDataWrapper
{
public:
    htps::sptr<ITTFont> getTTFont(const htps::str& rid) const;
    htps::sptr<ITexture> getTexture(const htps::str& rid) const;
    htps::sptr<IShader> getShader(const htps::str& rid) const;
    htps::sptr<IFont> getBMPFont(const htps::str& rid) const;
};

}  // namespace haf::res

#endif
