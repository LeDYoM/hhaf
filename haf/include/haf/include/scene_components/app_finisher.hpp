#ifndef HAF_SCENE_APP_FINISHER_INCLUDE_HPP
#define HAF_SCENE_APP_FINISHER_INCLUDE_HPP

#include <htypes/include/basic_property.hpp>
#include <htypes/include/str.hpp>
#include <haf/include/system/idatawrapper.hpp>

namespace haf::scene
{
class AppFinisher : public sys::IDataWrapper
{
public:
    /**
     * @brief This property can be set to tell
     * the system which app should be loaded next.
     * If not app is set, no app will be loaded.
     * It is not guaranteed that the app will be loaded.
     */
    htps::BasicProperty<htps::str> NextApp;
};

}  // namespace haf::scene

#endif
