#ifndef HAF_HOSTED_APP_IAPP_WITH_HOST_ACCESS_INCLUDE_HPP
#define HAF_HOSTED_APP_IAPP_WITH_HOST_ACCESS_INCLUDE_HPP

#include <hosted_app/include/iapp>

namespace haf
{
namespace host
{
class HostCommunication;
}

class IAppWithHostAccess : public IApp
{
public:
    constexpr IAppWithHostAccess() noexcept {}
    ~IAppWithHostAccess() override {}

    virtual void onHostInit(host::HostCommunication&) = 0;
};

}  // namespace haf

#endif
