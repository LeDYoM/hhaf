#pragma once

#ifndef HAF_SCENE_OBJECTFACTORY_INCLUDE_HPP
#define HAF_SCENE_OBJECTFACTORY_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/function.hpp>
#include <mtypes/include/str.hpp>

#include <mtypes/include/dictionary.hpp>

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
    using CreateReturnType          = mtps::uptr<InterfaceType>;
    using ObjectConstructorFunction = mtps::function<CreateReturnType(Args...)>;

    /**
     * @brief Constructs an ObjectFactory object
     */
    constexpr ObjectFactory() {}

    /**
     * @brief Destroy the Object Factory object
     */
    virtual ~ObjectFactory() {}

    /**
     * @brief Register a concrete object type with a given name and a
     *  construction function.
     *
     * @param type_name An @b mtps::str Representing the unique type name.
     * @param constructor_function The function that constructs the object.
     * @return true When the object type has been successfully registered.
     * @return false The object type cannot be registered.
     */
    bool registerObjectType(mtps::str type_name,
                            ObjectConstructorFunction constructor_function)
    {
        return constructors_.add(std::move(type_name),
                                 std::move(constructor_function), false);
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
                                  std::move(constructor_function));
    }

    /**
     * @brief Register a concrete object type with a given name and a
     *  construction function.
     *
     * @tparam T The concrete object type to be registered. Requires
     *  T::StaticTypeName to exists as a const char[] member
     * @param type_name An @b mtps::str Representing the unique type name.
     * @return true When the object type has been successfully registered.
     * @return false The object type cannot be registered.
     */
    template <typename T>
    constexpr bool registerObjectType(mtps::str type_name)
    {
        return registerObjectType(std::move(type_name),
                                  createObject<T, Args...>);
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
     * @brief Create an object instance from a previously registered type and
     * using the construction fucion provided using the arguments passed in
     * this call.
     *
     * @param type_name Previously registered type name.
     * @param args Args required by the construction function
     * @return CreateReturnType The object created or nullptr if the type name
     * does not exist.
     */
    CreateReturnType create(const mtps::str& type_name, Args... args)
    {
        if (!containsType(type_name))
        {
            return CreateReturnType(nullptr);
        }

        const auto iterator = constructors_.find(std::move(type_name));

        if (iterator == constructors_.cend())
        {
            return CreateReturnType(nullptr);
        }

        return (*iterator).second(std::forward<Args>(args)...);
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
        return create(T::StaticTypeName, std::forward<Args>(args)...);
    }

    /**
     * @brief Get the size (number of objects registered) of this factory
     *
     * @return The number of objects
     */
    constexpr mtps::size_type size() const { return constructors_.size(); }

    /**
     * @brief Ask if this instance contains any object registered
     *
     * @return true No objects in this instance
     * @return false At least one object in this instance
     */
    constexpr bool empty() const { return constructors_.empty(); }

private:
    mtps::Dictionary<ObjectConstructorFunction> constructors_;

    template <typename T, typename... Args>
    static CreateReturnType createObject(Args&&... args)
    {
        return mtps::muptr<T>(std::forward<Args>(args)...);
    }

    bool containsType(const mtps::str& name) const
    {
        return constructors_.find(name) != constructors_.cend();
    }
};
}  // namespace haf::utils

#endif
