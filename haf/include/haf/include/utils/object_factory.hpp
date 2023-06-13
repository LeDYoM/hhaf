HAF_PRAGMA_ONCE
#ifndef HAF_UTILS_OBJECT_FACTORY_INCLUDE_HPP
#define HAF_UTILS_OBJECT_FACTORY_INCLUDE_HPP

#include <haf/include/core/types.hpp>
#include <htypes/include/function.hpp>
#include <haf/include/core/types.hpp>

#include <htypes/include/dictionary.hpp>

namespace haf::utils
{

/**
 * @brief Factory class to create objects previously registered with a name.
 * This class provides a way of storing different functions to create objects
 * providing a common interface. The concrete type object will be provided
 * at time of object creation.
 *
 * You can make the type be automatically registerable by making providing
 * an inner member StaticTypeName.
 *
 * @tparam InterfaceType The interface type the construction functions will
 *      provide.
 * @tparam Args Arguments types to the construction function.
 */
template <typename InterfaceType, typename... Args>
class ObjectFactory
{
public:
    using CreateReturnType          = core::sptr<InterfaceType>;
    using ObjectConstructorFunction = htps::function<CreateReturnType(Args...)>;
    using size_type                 = core::size_type;

    /**
     * @brief Constructs an ObjectFactory object
     */
    constexpr ObjectFactory() = default;

    /**
     * @brief Destroy the Object Factory object
     */
    virtual ~ObjectFactory() = default;

    /**
     * @brief Register a concrete object type with a given name and a
     *  construction function.
     *
     * @param type_name An @b htps::str Representing the unique type name.
     * @param constructor_function The function that constructs the object.
     * @return true When the object type has been successfully registered.
     * @return false The object type cannot be registered.
     */
    bool registerObjectType(core::str_view type_name,
                            ObjectConstructorFunction constructor_function)
    {
        return constructors_.add(core::str{type_name},
                                 htps::move(constructor_function), false);
    }

    /**
     * @brief Register a concrete object type with a given name and a
     *  construction function.
     *
     * @tparam T The concrete object type to be registered. Requires
     *  @b T::StaticTypeName to exists as a const char[] member
     * @param constructor_function The function that constructs the object.
     * @return true When the object type has been successfully registered.
     * @return false The object type cannot be registered.
     */
    template <typename T>
    constexpr bool registerObjectType(
        ObjectConstructorFunction constructor_function)
    {
        return registerObjectType(T::StaticTypeName,
                                  htps::move(constructor_function));
    }

    /**
     * @brief Register a concrete object type with a given name and a
     *  construction function.
     *
     * @tparam T The concrete object type to be registered. Requires
     *  T::StaticTypeName to exists as a const char[] member
     * @param type_name An @b htps::str Representing the unique type name.
     * @return true When the object type has been successfully registered.
     * @return false The object type cannot be registered.
     */
    template <typename T>
    constexpr bool registerObjectType(core::str type_name)
    {
        return registerObjectType(core::str_view{type_name.c_str()},
                                  createObject<T, Args...>);
    }

    /**
     * @brief Register a concrete object type with a given name and a
     *  construction function.
     *
     * @tparam T The concrete object type to be registered. Requires
     *  T::StaticTypeName to exists as a const char[] member
     * @param type_name A char array Representing the unique type name.
     * @return true When the object type has been successfully registered.
     * @return false The object type cannot be registered.
     */
    template <typename T, size_type N>
    bool registerObjectType(char const (&type_name)[N])
    {
        return registerObjectType(type_name, createObject<T, Args...>);
    }

    /**
     * @brief Register a concrete object type. The name to register and the
     * constructor function are implicit. The name will be T::StaticTypeName
     * and the constructor function @b createObject<T, Args...>
     *
     * @return true When the object type has been successfully registered.
     * @return false The object type cannot be registered.
     */
    template <typename T>
    constexpr bool registerObjectType()
    {
        return registerObjectType(T::StaticTypeName, createObject<T, Args...>);
    }

    /**
     * @brief Unregister a concrete object type. Subsequent calls to create
     * will return nullptr as if the type name never existed.
     * @param type_name A char array Representing the unique type name.
     *
     * @return true When the object type has been successfully unregistered.
     * @return false The object type does not exist.
     */
    bool unregisterObjectType(core::str type_name)
    {
        size_type const size_previous{size()};
        constructors_.erase(htps::move(type_name));
        return size_previous > size();
    }

    /**
     * @brief Unregister a concrete object type. Subsequent calls to create
     * will return nullptr as if the type name never existed.
     * @tparam N Size of the char array
     * @param type_name A char array Representing the unique type name.
     *
     * @return true When the object type has been successfully unregistered.
     * @return false The object type does not exist.
     */
    template <size_type N>
    bool unregisterObjectType(char const (&type_name)[N])
    {
        return unregisterObjectType(core::str{type_name});
    }

    /**
     * @brief Unregister a concrete object type. Subsequent calls to create
     * will return nullptr as if the type name never existed.
     * @tparam T The type containing StaticTypeName to register.
     *
     * @return true When the object type has been successfully unregistered.
     * @return false The object type does not exist.
     */
    template <typename T>
    constexpr bool unregisterObjectType()
    {
        return unregisterObjectType(T::StaticTypeName);
    }

    /**
     * @brief Create an object instance from a previously registered type and
     * using the construction fucion provided using the arguments passed in
     * this call.
     *
     * @param type_name Previously registered type name.
     * @param args Args required by the construction function
     * @return CreateReturnType The object created or nullptr if the type name
     * does not exist.
     */
    CreateReturnType create(core::str_view const type_name, Args... args)
    {
        if (auto const iterator{constructors_.find(core::str{type_name})};
            iterator == constructors_.cend())
        {
            return CreateReturnType(nullptr);
        }
        else
        {
            return (*iterator).second(htps::forward<Args>(args)...);
        }
    }

    /**
     * @brief Create an object instance from a previously registered type and
     * using the construction fucion provided using the arguments passed in
     * this call.
     *
     * @tparam T Type of the concrete object to be created. The member
     * T::StaticTypeName must exist and will be used to search the registered
     * types.
     * @param args Args required by the construction function
     * @return CreateReturnType The object created or nullptr if the type name
     * does not exist.
     */
    template <typename T>
    constexpr CreateReturnType create(Args... args)
    {
        return create(T::StaticTypeName, htps::forward<Args>(args)...);
    }

    /**
     * @brief Get the size (number of objects registered) of this factory
     *
     * @return The number of objects
     */
    constexpr htps::size_type size() const { return constructors_.size(); }

    /**
     * @brief Ask if this instance contains any object registered
     *
     * @return true No objects in this instance
     * @return false At least one object in this instance
     */
    constexpr bool empty() const { return constructors_.empty(); }

private:
    htps::Dictionary<ObjectConstructorFunction> constructors_;

    template <typename T, typename... MArgs>
    static CreateReturnType createObject(MArgs&&... args)
    {
        return htps::msptr<T>(htps::forward<MArgs>(args)...);
    }

    bool containsType(core::str_view const name) const
    {
        return constructors_.cfind(name) != constructors_.cend();
    }
};
}  // namespace haf::utils

#endif
