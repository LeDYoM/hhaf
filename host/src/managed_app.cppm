module;

#include <hosted_app/include/iapp.hpp>

export module host:managed_app;

import htypes;

namespace haf::host
{
struct ManagedApp
{
    htps::rptr<IApp> app{nullptr};
    p_initApp init_app{nullptr};
    p_finishApp finish_app{nullptr};
    htps::str origin_file;
};

}  // namespace haf::host
