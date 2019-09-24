#pragma once

#ifndef MTYPES_DICTY_INCLUDE_HPP
#define MTYPES_DICTY_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "vector.hpp"
#include "dictionary.hpp"

namespace lib
{
    template <typename T>
    using KeyValuePair = pair<str,T>;

    using KeyValueStr = KeyValuePair<str>;
    using KeyValueObject = KeyValuePair<Object>;

    class Object
    {
    public:
        using ObjectDictionary = Dictionary<Object>;
        using ValueDictionary = Dictionary<str>;

        constexpr Object() {}

        inline Object(std::initializer_list<KeyValueStr> iListValues) 
        {
            set(std::move(iListValues), false);
        }

            inline Object(std::initializer_list<KeyValueObject> iListObjects)
            {
            set(std::move(iListObjects), false);
            }

        inline Object(std::initializer_list<KeyValueObject> iListObjects,
                std::initializer_list<KeyValueStr> iListValues)
        {
            set(std::move(iListObjects), false);
            set(std::move(iListValues), false);
        }

        inline Object(std::initializer_list<KeyValueStr> iListValues,
                std::initializer_list<KeyValueObject> iListObjects) 
        {
            set(std::move(iListValues), false);
            set(std::move(iListObjects), false);
        }

        constexpr bool operator==(const Object &obj) const noexcept 
        {
            return m_values == obj.m_values && m_objects == obj.m_objects;
        }

        constexpr bool operator!=(const Object &obj) const noexcept 
        {
            return !((*this) == obj);
        }

        class Value
        {
        public:
            constexpr Value() = default;
            constexpr Value(const Object *obj) : m_object{obj} {}
            constexpr Value(const str *val) : m_value{val} {}

            constexpr bool isValid() const noexcept { return m_object || m_value; }
            constexpr bool isValue() const noexcept { return m_value != nullptr; }
            constexpr bool isObject() const noexcept { return m_object != nullptr; }

            constexpr bool operator==(const str&key) const noexcept 
            {
                return ((isValue()) ? (*m_value) == key : false);
            }

            constexpr bool operator!=(const str&key) const noexcept 
            {
                return !(*this==key);
            }

            constexpr bool operator==(const Object &obj) const noexcept 
            {
                return ((isObject()) ? (*m_object) == obj : false);
            }

            constexpr bool operator!=(const Object &obj) const noexcept
            {
                return !(*this==obj);
            }

            constexpr bool operator==(const Value &obj) const noexcept
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

            constexpr bool operator!=(const Value &obj) const noexcept
            {
                return !(*this == obj);
            }

            Value operator[](const str&key) const
            {
                // Using indexing operator in a value returns empty value.
                // If the key exists, forward the key to it.
                return (isObject() ? (*m_object)[key] : Value{});
            }

            /// Get a @Value in the array form. That is the
            /// method is equivaled to obj(key){index].
            Value operator[](const size_t index) const
            {
                return (isObject() ? getObject()[index] : Value{});
            }

            const Object& getObject() const noexcept
            {
                return (*m_object);
            }

            const str& getValue() const noexcept
            {
                return (*m_value);
            }

            template <typename T>
            T as() const
            {
                return (*m_value).convertOrDefault<T>();
            }

        private:
            const Object *m_object{nullptr};
            const str *m_value{nullptr};
        };

        using KeyValueValue = KeyValuePair<Value>;

        constexpr size_type size_objects() const noexcept
        {
            return m_objects.size();
        }

        constexpr size_type size_values() const noexcept
        {
            return m_values.size();
        }

        constexpr size_type size() const noexcept
        {
            return size_objects() + size_values();
        }

        constexpr bool empty_objects() const noexcept
        {
            return m_objects.empty();
        }

        constexpr bool empty_values() const noexcept
        {
            return m_values.empty();
        }

        constexpr size_type empty() const noexcept
        {
            return empty_objects() && empty_values();
        }

        Value getObject(const str&key) const
        {
            auto token(m_objects.findChecked(key));
            return (token.first?
                Value(&(token.second->second)):
                Value());
        }

        Value getValue(const str&key) const
        {
            auto token(m_values.findChecked(key));
            return (token.first?
                Value(&(token.second->second)):
                Value());
        }

        /// Get a @Value pointing to an element with the specified key.
        /// @param[in] key Key str to search for.
        /// @return Empty invalid @Value if not found or a @Value
        /// pointing to the data if found.
        Value operator[](const str&key) const
        {
            // Note: Priority to str
            Value val{getValue(key)};
            return ((val.isValid()) ? val : getObject(key));
        }

        static constexpr const char*const arraySeparator = "::";

        /// Get a @Value in the array form.
        /// @param index The index of the element you want to read.
        /// @return @b Value Representing the element.
        /// Note: You might need to check with @Value::isValid
        /// if the value is valid.
        Value operator[](const size_t index) const
        {
            return (*this)[str(arraySeparator) + str::to_str(index)];
        }

        bool set(std::initializer_list<KeyValueStr> iListValues, bool overwrite = true)
        {
            bool ok{true};
            for (auto&& element : iListValues) 
            {
                ok &= m_values.add(std::move(element.first), std::move(element.second), overwrite);
            }
            return ok;
        }

        bool set(std::initializer_list<KeyValueObject> iListObject, bool overwrite = true)
        {
            bool ok{true};
            for (auto&& element : iListObject)
            {
                ok &= m_objects.add(element.first, element.second, overwrite);
            }
            return ok;
        }

        bool set(std::initializer_list<KeyValueValue> iListObject, bool overwrite = true)
        {
            bool ok{ true };
            for (auto&& element : iListObject)
            {
                if (element.second.isObject())
                {
                    ok &= set(element.first, element.second.getObject(), overwrite);
                }
                else if (element.second.isValue())
                {
                    ok &= set(element.first, element.second.getValue(), overwrite);
                }
                else
                {
                    ok = false;
                }
            }
            return ok;
        }

        bool set(str key, Object obj, bool overwrite = true)
        {
            return set({ std::make_pair(key, std::move(obj)) }, overwrite);
        }

        bool set(str key, str value, bool overwrite = true)
        {
            return set({ std::make_pair(key, std::move(value)) }, overwrite);
        }

        bool set(str key, Value value, bool overwrite = true)
        {
            return set({ std::make_pair(key, std::move(value)) }, overwrite);
        }

        bool set(size_t index, str value, bool overwrite = true)
        {
            return set({ std::make_pair(str(arraySeparator) + str::to_str(index), std::move(value)) }, overwrite);
        }

        template <typename T, typename TD = std::decay_t<T>,
            std::enable_if_t<std::is_arithmetic_v<TD>>* = nullptr>
        bool set(size_t index, T&& value, bool overwrite = true)
        {
            if constexpr (std::is_floating_point_v<TD>)
            {
                return set(index, str::to_str(static_cast<f64>(value)), overwrite);
            }
            else if constexpr (std::is_signed_v<TD>)
            {
                return set(index, str::to_str(static_cast<s64>(value)), overwrite);
            }
            else
            {
                return set(index, str::to_str(static_cast<u64>(value)), overwrite);
            }
        }
/*
        template <typename T>
        bool set(const vector<T>& value, bool overwrite = true)
        {
            bool is_set{true};
            size_t index{0U};
            for (const auto& element : value)
            {
                is_set &= set(index, value, overwrite);
            }
            return is_set;
        }
*/
        constexpr ObjectDictionary::iterator begin_objects() noexcept { return m_objects.begin(); }
        constexpr ObjectDictionary::const_iterator begin_objects() const noexcept{ return m_objects.begin(); }
        constexpr ObjectDictionary::iterator end_objects() noexcept { return m_objects.end(); }
        constexpr ObjectDictionary::const_iterator end_objects() const noexcept{ return m_objects.end(); }

        constexpr ValueDictionary::iterator begin_values() noexcept { return m_values.begin(); }
        constexpr ValueDictionary::const_iterator begin_values() const noexcept{ return m_values.begin(); }
        constexpr ValueDictionary::iterator end_values() noexcept { return m_values.end(); }
        constexpr ValueDictionary::const_iterator end_values() const noexcept{ return m_values.end(); }

    private:
        ValueDictionary m_values;
        ObjectDictionary m_objects;
    };
}

#endif
