#ifndef HAF_BACKEND_BACKEND_CREATOR_HPP
#define HAF_BACKEND_BACKEND_CREATOR_HPP

#include <htypes/include/types.hpp>
#include <backend/include/backend_factory.hpp>

extern "C"
{
    haf::backend::BackendFactory* createBackendFactory();
}

using BackendFactoryUPtr = htps::uptr<haf::backend::BackendFactory>;
using BackendFactoryPtr = htps::rptr<haf::backend::BackendFactory>;

#endif
