HTPS_PRAGMA_ONCE
#ifndef HAF_SCENE_APP_FINISHER_INCLUDE_HPP
#define HAF_SCENE_APP_FINISHER_INCLUDE_HPP

import htypes;

namespace haf::scene
{
class IAppFinisher
{
protected:
    virtual ~IAppFinisher() = default;

public:
    virtual bool setNextApp(htps::str const& next_app) = 0;
};

}  // namespace haf::scene

#endif
