#pragma once

#ifndef MTYPES_DICTY_INCLUDE_HPP
#define MTYPES_DICTY_INCLUDE_HPP

#include "types.hpp"
#include "str.hpp"

namespace lib
{
    class Dictionary
    {
    public:
		using element = std::pair<str, str>;
		using content = vector<element>;
		using iterator = content::iterator;
		using const_iterator = content::const_iterator;

        bool add(str key, str value, const bool overwrite = true)
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
    private:
		const_iterator find(const str &key) const noexcept {
			for (const auto& element : m_data) {
				if (element.first == key) {
					return &element;
				}
			}
			return m_data.cend();
		}

		iterator find(const str &key) noexcept {
			for (auto& element : m_data) {
				if (element.first == key) {
					return &element;
				}
			}
			return m_data.end();
		}

        content m_data;
    };
}

#endif
