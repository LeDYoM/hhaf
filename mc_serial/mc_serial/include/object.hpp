MCS_PRAGMA_ONCE
#ifndef MCS_OBJECT_INCLUDE_HPP
#define MCS_OBJECT_INCLUDE_HPP

#include <htypes/include/types.hpp>
#include <htypes/include/str.hpp>
#include <htypes/include/vector.hpp>
#include <htypes/include/array.hpp>
#include <htypes/include/dictionary.hpp>
#include <type_traits>
#include <utility>

namespace mcs
{

namespace tps = htps;
class Object;

template <typename T>
constexpr bool storable_as_value_v = std::is_arithmetic_v<std::decay_t<T>> ||
    std::is_same_v<std::decay_t<T>, tps::str>;

template <typename T>
constexpr bool is_object_v = std::is_same_v<std::decay_t<T>, Object>;

template <typename T>
constexpr bool storable_or_copyable_as_value_v =
    storable_as_value_v<T> || is_object_v<T>;

template <typename T>
using KeyValuePair = tps::pair<tps::str, T>;

using KeyValueStr    = KeyValuePair<tps::str>;
using KeyValueObject = KeyValuePair<Object>;

class Object
{
public:
    using ObjectDictionary = tps::Dictionary<Object>;
    using ValueDictionary  = tps::Dictionary<tps::str>;

    constexpr Object() noexcept = default;

    inline Object(std::initializer_list<KeyValueStr> iListValues)
    {
        set(tps::move(iListValues));
    }

    inline Object(std::initializer_list<KeyValueObject> iListObjects)
    {
        set(tps::move(iListObjects));
    }

    inline Object(std::initializer_list<KeyValueObject> iListObjects,
                  std::initializer_list<KeyValueStr> iListValues)
    {
        set(tps::move(iListObjects));
        set(tps::move(iListValues));
    }

    inline Object(std::initializer_list<KeyValueStr> iListValues,
                  std::initializer_list<KeyValueObject> iListObjects)
    {
        set(tps::move(iListValues));
        set(tps::move(iListObjects));
    }

    constexpr bool operator==(const Object& obj) const noexcept
    {
        return values_ == obj.values_ && objects_ == obj.objects_;
    }

    constexpr bool operator!=(const Object& obj) const noexcept
    {
        return !((*this) == obj);
    }

    class Value
    {
    public:
        constexpr Value() = default;
        constexpr Value(Object const* obj) : object_{obj} {}
        constexpr Value(tps::str const* val) : value_{val} {}

        constexpr bool isValid() const noexcept { return object_ || value_; }
        constexpr bool isValue() const noexcept { return value_ != nullptr; }
        constexpr bool isObject() const noexcept { return object_ != nullptr; }

        constexpr bool operator==(tps::str const& key) const noexcept
        {
            return ((isValue()) ? (*value_) == key : false);
        }

        constexpr bool operator!=(tps::str const& key) const noexcept
        {
            return !(*this == key);
        }

        constexpr bool operator==(Object const& obj) const noexcept
        {
            return ((isObject()) ? (*object_) == obj : false);
        }

        constexpr bool operator!=(Object const& obj) const noexcept
        {
            return !(*this == obj);
        }

        constexpr bool operator==(Value const& obj) const noexcept
        {
            if (isObject() == obj.isObject() && isValue() == obj.isValue())
            {
                if (isObject())
                {
                    return getObject() == obj.getObject();
                }
                else if (isValue())
                {
                    return getValue() == obj.getValue();
                }

                // Both are nullptr;
                return true;
            }
            return false;
        }

        constexpr bool operator!=(Value const& obj) const noexcept
        {
            return !(*this == obj);
        }

        [[nodiscard]] Value operator[](tps::str const& key) const
        {
            // Using indexing operator in a value returns empty value.
            // If the key exists, forward the key to it.
            return (isObject() ? (*object_)[key] : Value{});
        }

        /// Get a @Value in the array form. That is the
        /// method is equivaled to obj(key){index].
        [[nodiscard]] Value operator[](size_t const index) const
        {
            return (isObject() ? getObject()[index] : Value{});
        }

        [[nodiscard]] Object const& getObject() const noexcept
        {
            return (*object_);
        }

        [[nodiscard]] tps::str const& getValue() const noexcept
        {
            return (*value_);
        }

        template <typename T>
        [[nodiscard]] T as() const
        {
            if constexpr (std::is_enum_v<T>)
            {
                if constexpr (sizeof(T) == sizeof(char))
                {
                    return static_cast<T>(
                        (*value_).convertOrDefault<tps::s16>());
                }
                else
                {
                    return static_cast<T>(
                        (*value_)
                            .convertOrDefault<std::underlying_type_t<T>>());
                }
            }
            else if constexpr (std::is_same_v<T, tps::str>)
            {
                return (*value_);
            }
            else if constexpr (std::is_same_v<T, Object>)
            {
                return (*object_);
            }
            else
            {
                return (*value_).convertOrDefault<T>();
            }
        }

        template <typename T>
        bool as(T& value) const
        {
            if constexpr (std::is_enum_v<T>)
            {
                if constexpr (sizeof(T) == sizeof(char))
                {
                    auto [result, nval] = (*value_).convert<tps::s16>();
                    if (result)
                    {
                        value = static_cast<T>(nval);
                        return true;
                    }
                    return false;
                }
                else
                {
                    auto [result, nval] =
                        (*value_).convert<std::underlying_type_t<T>>();
                    if (result)
                    {
                        value = static_cast<T>(nval);
                        return true;
                    }
                    return false;
                }
            }
            else if constexpr (std::is_same_v<T, tps::str>)
            {
                if (value_ != nullptr)
                {
                    value = (*value_);
                    return true;
                }
                return false;
            }
            else if constexpr (std::is_same_v<T, Object>)
            {
                if (object_ != nullptr)
                {
                    value = (*object_);
                    return true;
                }
                return false;
            }
            else
            {
                if (value_ != nullptr)
                {
                    auto [result, nval] = (*value_).convert<T>();
                    if (result)
                    {
                        std::swap(value, nval);
                        return true;
                    }
                }
                return false;
            }
        }

        template <typename T>
        [[nodiscard]] bool as(tps::vector<T>& value) const
        {
            tps::vector<T> result;
            getObject() >> result;
            std::swap(result, value);
            return true;
        }

        template <typename T, tps::size_type Size>
        [[nodiscard]] bool as(tps::array<T, Size>& value) const
        {
            tps::array<T, Size> result;
            getObject() >> result;
            std::swap(result, value);
            return true;
        }

    private:
        const Object* object_{nullptr};
        const tps::str* value_{nullptr};
    };

    using KeyValueValue = KeyValuePair<Value>;

    constexpr tps::size_type size_objects() const noexcept
    {
        return objects_.size();
    }

    constexpr tps::size_type size_values() const noexcept
    {
        return values_.size();
    }

    constexpr tps::size_type size() const noexcept
    {
        return size_objects() + size_values();
    }

    constexpr bool empty_objects() const noexcept { return objects_.empty(); }

    constexpr bool empty_values() const noexcept { return values_.empty(); }

    constexpr tps::size_type empty() const noexcept
    {
        return empty_objects() && empty_values();
    }

    Value getObject(tps::str const& key) const
    {
        auto token{objects_.find_checked(key)};
        return (token.first ? Value(&(token.second->second)) : Value());
    }

    Value getValue(tps::str const& key) const
    {
        auto token(values_.find_checked(key));
        return (token.first ? Value(&(token.second->second)) : Value());
    }

    /**
     * @brief Get a @b Value pointing to an element with the specified key.
     *
     * @param[in] key Key str to search for
     * @return Empty invalid @b Value if not found or a @b Value
     * pointing to the data if found.
     */
    Value operator[](tps::str const& key) const
    {
        // Note: Priority to str
        Value val{getValue(key)};
        return ((val.isValid()) ? val : getObject(key));
    }

    Object* acquireObject(tps::str const& key) noexcept
    {
        auto token(objects_.find(key));
        return ((token != objects_.end()) ? &(token->second) : nullptr);
    }

    tps::str* acquireValue(tps::str const& key) noexcept
    {
        auto token(values_.find(key));
        return ((token != values_.end()) ? &(token->second) : nullptr);
    }

    static constexpr const char* const arraySeparator = "::";

    /**
     * @brief Get a @b Value in the array form.
     *
     * @param index The index of the element you want to read.
     * @return Value Representing the element.
     * Note: You might need to check with @Value::isValid
     * if the value is valid.
     */
    Value operator[](const size_t index) const
    {
        return (*this)[tps::str(arraySeparator) + tps::str::to_str(index)];
    }

    bool set(std::initializer_list<KeyValueStr> iListValues)
    {
        bool ok{true};
        for (auto&& element : iListValues)
        {
            ok &= values_.add(element.first, element.second);
        }
        return ok;
    }

    bool set(std::initializer_list<KeyValueObject> iListObject)
    {
        bool ok{true};
        for (auto&& element : iListObject)
        {
            ok &= objects_.add(element.first, element.second);
        }
        return ok;
    }

    bool set(std::initializer_list<KeyValueValue> iListObject)
    {
        bool ok{true};
        for (auto&& element : iListObject)
        {
            if (element.second.isObject())
            {
                ok &= set(element.first, element.second.getObject());
            }
            else if (element.second.isValue())
            {
                ok &= set(element.first, element.second.getValue());
            }
            else
            {
                ok = false;
            }
        }
        return ok;
    }

    bool set(tps::str key, Object obj)
    {
        return set({std::make_pair(tps::move(key), tps::move(obj))});
    }

    bool set(tps::str key, tps::str value)
    {
        return set({std::make_pair(tps::move(key), tps::move(value))});
    }

    bool set(tps::str key, Value value)
    {
        return set({std::make_pair(tps::move(key), tps::move(value))});
    }

    template <typename T,
              typename TD                           = std::decay_t<T>,
              std::enable_if_t<std::is_arithmetic_v<TD> ||
                               std::is_enum_v<TD>>* = nullptr>
    bool set(tps::str key, T&& value)
    {
        if constexpr (std::is_enum_v<TD>)
        {
            return set(tps::move(key),
                       tps::str::to_str(static_cast<std::underlying_type_t<TD>>(
                           tps::forward<T>(value))));
        }
        else if constexpr (std::is_floating_point_v<TD>)
        {
            return set(tps::move(key),
                       tps::str::to_str(
                           static_cast<tps::f64>(tps::forward<T>(value))));
        }
        else if constexpr (std::is_signed_v<TD>)
        {
            return set(tps::move(key),
                       tps::str::to_str(
                           static_cast<tps::s64>(tps::forward<T>(value))));
        }
        else
        {
            return set(tps::move(key),
                       tps::str::to_str(
                           static_cast<tps::u64>(tps::forward<T>(value))));
        }
    }

    bool set(size_t index, tps::str value)
    {
        return set(
            {std::make_pair(tps::str(arraySeparator) + tps::str::to_str(index),
                            tps::move(value))});
    }

    bool set(size_t index, Object value)
    {
        return set(tps::str(arraySeparator) + tps::str::to_str(index),
                   tps::move(value));
    }

    template <typename T,
              typename TD                                 = std::decay_t<T>,
              std::enable_if_t<std::is_arithmetic_v<TD>>* = nullptr>
    bool set(size_t index, T&& value)
    {
        if constexpr (std::is_floating_point_v<TD>)
        {
            return set(index,
                       tps::str::to_str(
                           static_cast<tps::f64>(tps::forward<T>(value))));
        }
        else if constexpr (std::is_signed_v<TD>)
        {
            return set(index,
                       tps::str::to_str(
                           static_cast<tps::s64>(tps::forward<T>(value))));
        }
        else
        {
            return set(index,
                       tps::str::to_str(
                           static_cast<tps::u64>(tps::forward<T>(value))));
        }
    }

    template <typename T>
    bool set(tps::str const& property_name, tps::vector<T> const& value)
    {
        Object inner_object;
        inner_object << value;
        return set(property_name, inner_object);
    }

    template <typename T, tps::size_type Size>
    bool set(tps::str const& property_name, tps::array<T, Size> const& value)
    {
        Object inner_object;
        inner_object << value;
        return set(property_name, inner_object);
    }

    constexpr ObjectDictionary::iterator begin_objects() noexcept
    {
        return objects_.begin();
    }
    constexpr ObjectDictionary::const_iterator begin_objects() const noexcept
    {
        return objects_.begin();
    }
    constexpr ObjectDictionary::iterator end_objects() noexcept
    {
        return objects_.end();
    }
    constexpr ObjectDictionary::const_iterator end_objects() const noexcept
    {
        return objects_.end();
    }

    constexpr ValueDictionary::iterator begin_values() noexcept
    {
        return values_.begin();
    }
    constexpr ValueDictionary::const_iterator begin_values() const noexcept
    {
        return values_.begin();
    }
    constexpr ValueDictionary::iterator end_values() noexcept
    {
        return values_.end();
    }
    constexpr ValueDictionary::const_iterator end_values() const noexcept
    {
        return values_.end();
    }

    constexpr ObjectDictionary const& objects() const noexcept
    {
        return objects_;
    }

    constexpr ValueDictionary const& values() const noexcept { return values_; }

    template <typename T>
    constexpr static bool isArrayElement(tps::pair<tps::str, T> const& it)
    {
        return (it.first.starts_with(tps::str(arraySeparator)));
    }

private:
    ValueDictionary values_;
    ObjectDictionary objects_;
};

//////////////////////////////////////////////////////////////////////////////////

template <typename T>
constexpr const Object& operator>>(Object const& obj, tps::vector<T>& data)
{
    bool stay{true};
    for (tps::size_type count{0U}; stay; ++count)
    {
        const Object::Value& value = obj[count];
        stay                       = value.isValid();
        if (stay)
        {
            T internal_data;

            if constexpr (storable_or_copyable_as_value_v<T>)
            {
                if constexpr (is_object_v<T>)
                {
                    value.getObject() >> internal_data;
                }
                else
                {
                    if constexpr (storable_as_value_v<T>)
                    {
                        value.getValue() >> internal_data;
                    }
                }
            }
            else if constexpr (std::is_enum_v<T>)
            {
                value.getValue() >> internal_data;
            }
            else
            {
                value.getObject() >> internal_data;
            }
            data.push_back(tps::move(internal_data));
        }
    }
    return obj;
}

template <typename T, tps::size_type Size>
constexpr Object const& operator>>(const Object& obj, tps::array<T, Size>& data)
{
    tps::vector<T> temp;
    obj >> temp;
    data = tps::array<T, Size>{temp.cbegin(), temp.cend()};
    return obj;
}

//////////////////////////////////////////////////////////////////

template <typename T>
inline Object& operator<<(Object& obj, tps::vector<T> const& data)
{
    tps::size_type counter{0U};
    for (const auto& element : data)
    {
        if constexpr (storable_or_copyable_as_value_v<T>)
        {
            obj.set(counter++, element);
        }
        else if constexpr (std::is_enum_v<T>)
        {
            obj.set(counter++, static_cast<std::underlying_type_t<T>>(element));
        }
        else
        {
            Object temp;
            temp << element;
            obj.set(counter++, temp);
        }
    }
    return obj;
}

template <typename T, tps::size_type Size>
inline Object& operator<<(Object& obj, tps::array<T, Size> const& data)
{
    tps::vector<T> temp(data.cbegin(), data.cend());
    obj << temp;
    return obj;
}

}  // namespace mcs

#endif
