#include <backend/include/backend_creator.hpp>
#include <hlog/include/hlog.hpp>

haf::backend::BackendFactory* createBackendFactory()
{
    return new haf::backend::BackendFactory();
}
