#ifndef HAF_BACKEND_BACKEND_CREATOR_HPP
#define HAF_BACKEND_BACKEND_CREATOR_HPP

#include <backend/include/backend_factory.hpp>

import htypes;

extern "C"
{
    haf::backend::BackendFactory* createBackendFactory();
    void destroyBackendFactory(haf::backend::BackendFactory*);
}

using BackendFactoryUPtr = htps::uptr<haf::backend::BackendFactory>;
using BackendFactoryPtr  = htps::rptr<haf::backend::BackendFactory>;

#endif
