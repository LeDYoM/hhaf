#include <backend/include/backend_creator.hpp>

lib::backend::BackendFactory* createBackendFactory()
{
    return new lib::backend::BackendFactory();
}

void destroyBackendFactory(lib::backend::BackendFactory*b_factory)
{
    delete b_factory;
}
