#include <backend_client/include/default_backend_manager.hpp>
#include <backend_dev/include/ibackendregister.hpp>

#include <htypes/include/vector.hpp>

using namespace htps;

namespace haf::backend::client
{
struct DefaultBackendManager::DefaultBackendManagerPrivate
{
    htps::vector<htps::uptr<IAutoRegisterFactory>> factories;
    void pushFactory(htps::uptr<IAutoRegisterFactory> f);
};

DefaultBackendManager::DefaultBackendManager() :
    priv_{make_pimplp<DefaultBackendManagerPrivate>()}
{}

void DefaultBackendManager::setFactories(
    rptr<IBackendRegister> const backend_register)
{
    for (auto&& factory : priv_->factories)
    {
        factory.get()->setFactory(backend_register);
    }
}

void DefaultBackendManager::resetFactories(
    rptr<IBackendRegister> const backend_register)
{
    for (auto&& factory : priv_->factories)
    {
        factory.get()->resetFactory(backend_register);
    }
}

void DefaultBackendManager::destroy()
{
    for (auto&& factory : priv_->factories)
    {
        factory.get()->destroy();
    }
}

DefaultBackendManager::~DefaultBackendManager()
{
    destroy();
}

void DefaultBackendManager::pushFactory(uptr<IAutoRegisterFactory> f)
{
    priv_->factories.push_back(htps::move(f));
}

}  // namespace haf::backend::client
