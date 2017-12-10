#pragma once

#ifndef __LIB_RESOURCEMANAGER_HPP__
#define __LIB_RESOURCEMANAGER_HPP__

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include "appservice.hpp"
#include <list>

namespace lib
{
	namespace scene
	{
		class TTFont;
		class Texture;
	}
	namespace core
	{
		class Resource;

		class ResourceManager final : public AppService
		{
		public:
			ResourceManager();
			~ResourceManager();

			sptr<scene::TTFont> getFont(const str &rid, const str &fileName);
			sptr<scene::Texture> getTexture(const str &rid, const str &fileName);

			template <typename T>
			sptr<T> getResource(const str &rid, const str &fileName="");

			template <>
			sptr<scene::TTFont> getResource(const str &rid, const str &fileName) { return getFont(rid, fileName); }

			template <>
			sptr<scene::Texture> getResource(const str &rid, const str &fileName) { return getTexture(rid, fileName); }

			template <typename T>
			using NamedIndex = std::pair<const str, T>;

			template <typename T>
			using ResourceList = std::list<NamedIndex<T>>;

		private:
			ResourceList<sptr<scene::TTFont>> m_fonts;
			ResourceList<sptr<scene::Texture>> m_textures;
		};
	}
}

#endif
