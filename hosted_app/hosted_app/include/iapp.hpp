#ifndef HAF_HOSTED_APP_IAPP_INCLUDE_HPP
#define HAF_HOSTED_APP_IAPP_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <host_connector/include/ihost_connector.hpp>

namespace haf::scene
{
class IAppInitializer;
class IAppFinisher;
}  // namespace haf::scene

namespace haf
{
class IApp
{
public:
    /**
     * @brief Empty defaulted constexpr constructor.
     */
    constexpr IApp() noexcept {}

    /**
     * @brief Destroy the IApp object. This destructor is intended
     * to be empty in this class
     */
    virtual ~IApp() {}

    /**
     * @brief Initialization function. This function will be invoked
     * from the haf system to initialize the app. An @b IAppInitializer
     * instance will provide with the necessary data and members to
     * perform some initialization actions.
     *
     * @param app_initializer Class to help the app perform initialization
     * actions.
     */
    virtual void onInit(scene::IAppInitializer& app_initializer) = 0;

    /**
     * @brief Destroying function. This function will be invoked from the
     * haf system before destroying this App. An @b IAppFinisher will be
     * provided to help in deinitialize actions.
     *
     * @param app_finisher Class to help the app perform destruction
     */
    virtual void onFinish(scene::IAppFinisher& app_finisher) = 0;

    /**
     * @brief Function that should retrieve the version of the app.
     * @return htps::u16 Current version (high)
     */
    virtual htps::u16 getVersion() const noexcept = 0;

    /**
     * @brief Function that should retrieve the subversion of the app.
     * @return htps::u16 Current subversion (medium)
     */
    virtual htps::u16 getSubVersion() const noexcept = 0;

    /**
     * @brief Function that should retrieve the patch of the app.
     * @return htps::u16 Current path
     */
    virtual htps::u16 getPatch() const noexcept = 0;

    /**
     * @brief Function that should retrieve the tweak of the app.
     * @return htps::u16 Current tweak
     */
    virtual htps::u16 getTweak() const noexcept = 0;

    /**
     * @brief Function that should retrieve the name of the app.
     * @return htps::str Name of the app.
     */
    virtual htps::str getName() const noexcept = 0;
};

using p_initApp   = IApp* (*)();
using p_finishApp = bool (*)(IApp* const);

}  // namespace haf

#endif
