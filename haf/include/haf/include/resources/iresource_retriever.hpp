#ifndef HAF_RESOURCES_RESOURCE_RETRIVER_INCLUDE_HPP
#define HAF_RESOURCES_RESOURCE_RETRIVER_INCLUDE_HPP

#include <haf/include/types/basic_types.hpp>

namespace haf::res
{
class IFont;
class ITTFont;
class ITexture;
class IShader;

class IResourceRetriever
{
public:
    virtual ~IResourceRetriever() = default;

    virtual types::sptr<ITTFont> getTTFont(types::str const& rid) const = 0;
    virtual types::sptr<ITexture> getTexture(types::str const& rid) const = 0;
    virtual types::sptr<IShader> getShader(types::str const& rid) const = 0;
    virtual types::sptr<IFont> getBMPFont(types::str const& rid) const = 0;
};

}  // namespace haf::res

#endif
