#include <backend/include/backend_creator.hpp>

haf::backend::BackendFactory* createBackendFactory()
{
    return new haf::backend::BackendFactory();
}

void destroyBackendFactory(haf::backend::BackendFactory*b_factory)
{
    delete b_factory;
}
