HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_APP_FINISHER_INCLUDE_HPP
#define HAF_SCENE_APP_FINISHER_INCLUDE_HPP

#include <htypes/include/str.hpp>

namespace haf::scene
{
class IAppFinisher
{
protected:
    virtual ~IAppFinisher() = default;
};

}  // namespace haf::scene

#endif
