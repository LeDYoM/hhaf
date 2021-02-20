#include <backend_client/include/default_backend_manager.hpp>
#include <backend_client/include/ibackendregister.hpp>

#include <htypes/include/vector.hpp>

using namespace htps;

namespace haf::backend::client
{
struct DefaultBackendManager::DefaultBackendManagerPrivate
{
    htypes::vector<htps::uptr<IAutoRegisterFactory>> factories;
    void pushFactory(htps::uptr<IAutoRegisterFactory> f);

};

DefaultBackendManager::DefaultBackendManager() :
    priv_{std::make_unique<DefaultBackendManagerPrivate>()}
{}

void DefaultBackendManager::setFactories(
    rptr<IBackendRegister> const backend_register)
{
    for (auto const& factory : priv_->factories)
    {
        factory.get()->setFactory(backend_register);
    }
}

void DefaultBackendManager::resetFactories(
    rptr<IBackendRegister> const backend_register)
{
    for (auto const& factory : priv_->factories)
    {
        factory.get()->resetFactory(backend_register);
    }
}

void DefaultBackendManager::destroy()
{
    for (const auto& factory : priv_->factories)
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
    priv_->factories.emplace_back(std::move(f));
}

}  // namespace haf::backend::client
