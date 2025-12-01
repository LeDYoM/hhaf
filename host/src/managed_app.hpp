#ifndef HAF_HOST_MANAGED_APP_INCLUDE_HPP
#define HAF_HOST_MANAGED_APP_INCLUDE_HPP

import htypes;

#include <hosted_app/include/iapp.hpp>

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

#endif
