export module backend:backend_creator;

import :backend_factory;
import htypes;

extern "C"
{
    export haf::backend::BackendFactory* createBackendFactory()
    {
        return new haf::backend::BackendFactory();
    }

    export void destroyBackendFactory(haf::backend::BackendFactory*)
    {

    }
}

export using BackendFactoryUPtr = htps::uptr<haf::backend::BackendFactory>;
export using BackendFactoryPtr  = htps::rptr<haf::backend::BackendFactory>;
