#ifndef HAF_HOSTED_APP_IAPP_WITH_HOST_ACCESS_INCLUDE_HPP
#define HAF_HOSTED_APP_IAPP_WITH_HOST_ACCESS_INCLUDE_HPP

namespace haf::host
{
class HostCommunication;
}

namespace haf::user
{
template <typename BaseApp>
class IAppWithHostAccess : public BaseApp
{
public:
    constexpr IAppWithHostAccess() noexcept {}
    ~IAppWithHostAccess() override {}

    virtual void onHostInit(host::HostCommunication&) = 0;
};

}  // namespace haf::user

#endif
