#ifndef HAF_BACKEND_BACKEND_CREATOR_HPP
#define HAF_BACKEND_BACKEND_CREATOR_HPP

#include <htypes/include/types.hpp>
#include <backend/include/backendfactory.hpp>

extern "C"
{
    haf::backend::BackendFactory* createBackendFactory();
    void destroyBackendFactory(haf::backend::BackendFactory*);
}

using BackendFactoryUPtr = htps::uptr<haf::backend::BackendFactory,
                                      void (*)(haf::backend::BackendFactory*)>;

using BackendFactoryPtr = htps::rptr<haf::backend::BackendFactory>;

#endif
