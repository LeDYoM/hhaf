#ifndef HAF_BACKEND_FACTORY_HPP
#define HAF_BACKEND_FACTORY_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>

namespace agloader
{
class Loader;
}

namespace haf::backend
{
class BackendRegister;
class IWindow;

/**
 * @brief Class representing a factory for backend classes.
 * This class initializes and stores subsystems of a backend.
 */
class BackendFactory final
{
public:
    BackendFactory();
    ~BackendFactory();

    static constexpr char StaticTypeName[] = "BackendFactory";

    /**
     * @brief Load a new shared object containing factories to be used by haf
     *
     * @param file_name File name containing the backend factories library to
     * load
     * @return true Successfully load
     * @return false Failed in loading
     */
    bool loadBackendFile(htps::str const& file_name);

    htps::rptr<IWindow> getWindow() const noexcept;

    bool isWindowFactoryAvailable() const noexcept;

private:
    using BackendRegisterUptr = htps::uptr<BackendRegister>;
    htps::vector<BackendRegisterUptr>
        loaded_modules_;  //< List of loaded backend libraries.
    void selectFactoriesToUse(
        BackendRegisterUptr const& backend_register) noexcept;
    htps::rptr<IWindow> window_{nullptr};
    htps::rptr<agloader::Loader> loader_{nullptr};
};
}  // namespace haf::backend

#endif
