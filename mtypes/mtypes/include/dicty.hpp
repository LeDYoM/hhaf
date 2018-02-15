#pragma once

#ifndef MTYPES_DICTY_INCLUDE_HPP
#define MTYPES_DICTY_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "vector.hpp"

namespace lib::dicty
{
    class Object;

    template <typename T>
    class BasicDictionary
    {
    public:
        using value = T;
        using element = std::pair<str, value>;
        using content = vector<element>;
        using iterator = typename content::iterator;
        using const_iterator = typename content::const_iterator;

		constexpr BasicDictionary() = default;

		constexpr BasicDictionary(std::initializer_list<element> eList)
            : m_data{ eList } {}

		constexpr BasicDictionary(const content &eList)
            : m_data{ eList } {}

		constexpr bool add(const content &eList, const bool overwrite = true)
        {
            bool result{ true };
            for (const element& elems : eList) {
                result &= add(elems.first, elems.second, overwrite);
            }
            return result;
        }

		constexpr bool add(std::initializer_list<element> eList, const bool overwrite = true)
        {
            bool result{true};
            for (const element& elems : eList) {
                result &= add(elems.first, elems.second, overwrite);
            }
            return result;
        }

		constexpr bool add(str key, T value, const bool overwrite = true)
        {
            auto it(find(key));

            if (it == m_data.cend()) {
                m_data.emplace_back(std::move(key), std::move(value));
                return true;
            }
            else if (overwrite) {
                (*it) = element(key, value);
                return true;
            }
            return false;
        }

        constexpr void clear() {
            m_data.clear();
        }

        constexpr const content &data() const noexcept {
            return m_data;
        }

    private:
        constexpr const_iterator find(const str &key) const noexcept {
            for (auto &element : m_data) {
                if (element.first == key) {
                    return &element;
                }
            }
            return m_data.cend();
        }

        constexpr iterator find(const str &key) noexcept {
            for (auto &element : m_data) {
                if (element.first == key) {
                    return &element;
                }
            }
            return m_data.end();
        }

        constexpr bool exists(const str &key) noexcept {
            return find(key) != m_data.end();
        }

        constexpr bool exists(const str &key) const noexcept {
            return find(key) != m_data.cend();
        }

		constexpr std::pair<bool,iterator> findChecked(const str&key) noexcept
        {
            auto iterator(find(key));
            return {iterator != m_data.end(), iterator};
        }

		constexpr std::pair<bool,const_iterator> findChecked(const str&key) const noexcept
        {
            auto iterator(find(key));
            return {iterator != m_data.cend(), iterator};
        }

        content m_data;
        friend class Object;
    };

    class Value
    {
    public:
        constexpr Value() = default;
        constexpr Value(Object *obj) : m_object{obj} {}
        constexpr Value(str *data) : m_data{data} {}

        constexpr bool isValid() const noexcept { return m_object || m_data; }
    private:
        Object *m_object{nullptr};
        str *m_data{nullptr};
    };

    class Object
    {
    public:
        using ObjectDictionary = BasicDictionary<Object>;
        using ValueDictionary = BasicDictionary<str>;

        constexpr Object() {}

		constexpr Object(const std::initializer_list<std::pair<str,str>> iListValues) {
            set(iListValues);
        }

		constexpr Object(const std::initializer_list<std::pair<str,Object>> iListObjects) {
			set(iListObjects);
        }

		constexpr Object(std::initializer_list<std::pair<str, Object>> iListObjects,
	            std::initializer_list<std::pair<str, str>> iListValues) {
			set(iListObjects);
			set(iListValues);
		}

		constexpr Object(std::initializer_list<std::pair<str, str>> iListValues,
               std::initializer_list<std::pair<str, Object>> iListObjects) {
			set(iListValues);
			set(iListObjects);
		}

        Value getObject(const str&key) {
            auto token(m_objects.findChecked(key));
            return (token.first?
                Value(&(token.second->second)):
                Value());
        }

        Value getValue(const str&key) {
            auto token(m_values.findChecked(key));
            return (token.first?
                Value(&(token.second->second)):
                Value());
        }

		template <typename... Args>
		Value getObject(const str&key, Args&&... args) {
			Value v{ std::move(getObject(key)) };
			if constexpr (sizeof...(args) > 0) {
				return (v.isValid()) ?
					return getObject(std::forward<Args>(args)...)
					: v;
			}
			return v;
		}


    private:
        constexpr bool set(const std::initializer_list<std::pair<str, str>> iListValues, bool overwrite = true)
        {
            bool ok{true};
            for (auto&& element : iListValues) {
                ok &= m_values.add(element.first,element.second, overwrite);
            }
            return ok;
        }

        constexpr bool set(const std::initializer_list<std::pair<str,Object>> iListObject, bool overwrite = true)
        {
            bool ok{true};
            for (auto&& element : iListObject) {
                ok &= m_objects.add(element.first, element.second, overwrite);
            }
            return ok;
        }

        ValueDictionary m_values;
        ObjectDictionary m_objects;
    };
}

#endif
