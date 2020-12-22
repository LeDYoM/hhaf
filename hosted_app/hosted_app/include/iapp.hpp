#ifndef HAF_IAPP_INCLUDE_HPP
#define HAF_IAPP_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace haf::sys
{
class DataWrapperCreator;
}  // namespace haf::sys

namespace haf::scene
{
class AppInitializer;
}

namespace haf
{
class IApp
{
public:
    constexpr IApp() noexcept {}
    virtual ~IApp() noexcept {}

    virtual void onInit(scene::AppInitializer& data_wrapper_creator) = 0;
    virtual void onFinish(sys::DataWrapperCreator& data_wrapper_creator)    = 0;

    virtual mtps::u16 getVersion() const noexcept    = 0;
    virtual mtps::u16 getSubVersion() const noexcept = 0;
    virtual mtps::u16 getPatch() const noexcept      = 0;
    virtual mtps::u16 getTweak() const noexcept      = 0;
    virtual mtps::str getName() const noexcept       = 0;
};
}  // namespace haf

using p_initApp   = haf::IApp* (*)();
using p_finishApp = bool (*)(haf::IApp* const);

#endif
