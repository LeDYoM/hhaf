#pragma once

#ifndef MTYPES_DICTY_INCLUDE_HPP
#define MTYPES_DICTY_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"
#include "vector.hpp"

namespace lib::dicty
{
    class Object;

	/// This class contains a group of keys and their associated values.
	/// It is used as a component for the @Object class.
    template <typename T>
    class BasicDictionary
    {
    public:
        using value_type = T;
        using element = pair<str, value_type>;
        using content = vector<element>;
        using iterator = typename content::iterator;
        using const_iterator = typename content::const_iterator;

		/// Default constructor.
        constexpr BasicDictionary() = default;

        constexpr BasicDictionary(std::initializer_list<element> eList)
            : m_data{ std::move(eList) } {}

        constexpr BasicDictionary(const content &eList)
            : m_data{ std::move(eList) } {}

        constexpr bool add(const content &eList, const bool overwrite = true)
        {
            bool result{ true };
            for (const element& elems : eList) 
			{
                result &= add(elems.first, elems.second, overwrite);
            }
            return result;
        }

        constexpr bool add(std::initializer_list<element> eList, const bool overwrite = true)
        {
            bool result{true};
            for (const element& elems : eList) 
			{
                result &= add(elems.first, elems.second, overwrite);
            }
            return result;
        }

        constexpr bool add(str key, T value, const bool overwrite = true)
        {
            auto it(find(key));

            if (it == m_data.cend()) 
			{
                m_data.emplace_back(std::move(key), std::move(value));
                return true;
            }
            else if (overwrite) 
			{
                (*it) = element(key, value);
                return true;
            }
            return false;
        }

        constexpr void clear() 
		{
            m_data.clear();
        }

        constexpr const content &data() const noexcept 
		{
            return m_data;
        }

    private:
        constexpr const_iterator find(const str &key) const noexcept 
		{
            for (auto &element : m_data) 
			{
                if (element.first == key) 
				{
                    return &element;
                }
            }
            return m_data.cend();
        }

        constexpr iterator find(const str &key) noexcept 
		{
            for (auto&& element : m_data) 
			{
                if (element.first == key) 
				{
                    return &element;
                }
            }
            return m_data.end();
        }

        constexpr bool exists(const str &key) const noexcept 
		{
            return find(key) != m_data.cend();
        }

        constexpr pair<bool,iterator> findChecked(const str&key) noexcept
        {
            auto iterator(find(key));
            return {iterator != m_data.end(), iterator};
        }

        constexpr pair<bool,const_iterator> findChecked(const str&key) const noexcept
        {
            const auto it(find(key));
            return {it != m_data.cend(), it};
        }

        constexpr size_type size() const noexcept 
		{
            return m_data.size();
        }

		constexpr bool empty() const noexcept
		{
			return m_data.empty();
		}

        constexpr bool operator==(const BasicDictionary &other) const noexcept 
		{
            if (m_data.size() == other.m_data.size()) 
			{
				for (size_type i = { 0U }; i < m_data.size(); ++i)
				{
                    if (m_data[i].first != other.m_data[i].first) 
					{
                        return false;
                    }
                    else if (m_data[i].second != other.m_data[i].second) 
					{
                        return false;
                    }
                }
                return true;
            }
            return false;
        }

        constexpr bool operator!=(const BasicDictionary &other) const noexcept 
		{
            return !(*this == other);
        }

        content m_data;
        friend class Object;
    };

    class Object
    {
    public:
        using ObjectDictionary = BasicDictionary<Object>;
        using ValueDictionary = BasicDictionary<str>;

        constexpr Object() {}

        inline Object(std::initializer_list<pair<str,str>> iListValues) 
		{
            set(std::move(iListValues), false);
        }

         inline Object(std::initializer_list<pair<str,Object>> iListObjects)
		 {
            set(std::move(iListObjects), false);
         }

        inline Object(std::initializer_list<pair<str, Object>> iListObjects,
                std::initializer_list<pair<str, str>> iListValues)
		{
            set(std::move(iListObjects), false);
            set(std::move(iListValues), false);
        }

        inline Object(std::initializer_list<pair<str, str>> iListValues,
               std::initializer_list<pair<str, Object>> iListObjects) 
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

        private:
            const Object *m_object{nullptr};
            const str *m_value{nullptr};
        };


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
			return (*this)[str(arraySeparator) + str(index)];
		}

		bool set(std::initializer_list<pair<str, str>> iListValues, bool overwrite = true)
        {
            bool ok{true};
            for (auto&& element : iListValues) 
			{
                ok &= m_values.add(std::move(element.first), std::move(element.second), overwrite);
            }
            return ok;
        }

        bool set(std::initializer_list<pair<str,Object>> iListObject, bool overwrite = true)
        {
            bool ok{true};
            for (auto&& element : iListObject)
			{
                ok &= m_objects.add(element.first, element.second, overwrite);
            }
            return ok;
        }

		bool set(std::initializer_list<pair<str, Value>> iListObject, bool overwrite = true)
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
			return set({ std::make_pair(key, obj) }, overwrite);
		}

		bool set(str key, str value, bool overwrite = true)
		{
			return set({ std::make_pair(key, value) }, overwrite);
		}

		bool set(str key, Value value, bool overwrite = true)
		{
			return set({ std::make_pair(key, value) }, overwrite);
		}

	private:
        ValueDictionary m_values;
        ObjectDictionary m_objects;
    };
}

#endif
