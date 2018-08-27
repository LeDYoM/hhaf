#include "resourcemanager.hpp"
#include <lib/include/core/log.hpp>

#include <lib/scene/ttfont.hpp>
#include <lib/scene/texture.hpp>
#include <lib/scene/shader.hpp>

#include <lib/core/backendfactory.hpp>
#include <algorithm>
#include <list>

namespace lib::core
{
    template <typename T>
    using NamedIndex = pair<const str, T>;

    template <typename T>
    using ResourceList = std::list<NamedIndex<T>>;

    namespace
	{
        template <typename T, typename A>
        inline auto get_or_add(A& factory, ResourceList<sptr<T>> &container, const str &rid, const str &fileName)
        {
            auto iterator(std::find_if(container.begin(), container.end(),
                [rid](const auto &node) {return node.first == rid; }));

            if (iterator != container.end())
            {
                return (*iterator).second;
            }
            else
            {
                // Not found, try to load it.
                auto resource(msptr<T>(factory.loadFromFile(fileName)));
                container.push_back(NamedIndex<sptr<T>>(rid, resource));
                return resource;
            }
        }

        template <typename T, typename A>
        inline auto get_or_default(A& /*factory*/, ResourceList<sptr<T>> &container, const str &rid)
        {
            auto iterator(std::find_if(container.begin(), container.end(),
                [rid](const auto &node) {return node.first == rid; }));

            return (iterator != container.end()) ?
                (*iterator).second
                :
                msptr<T>(nullptr);
        }
    }

    struct ResourceManager::ResourceManagerPrivate
    {
        ResourceList<sptr<scene::TTFont>> m_fonts;
        ResourceList<sptr<scene::Texture>> m_textures;
		ResourceList<sptr<scene::Shader>> m_shaders;
    };

    ResourceManager::ResourceManager() : AppService{}, m_private{ muptr<ResourceManagerPrivate>() } {}
	ResourceManager::~ResourceManager() = default;

	sptr<scene::TTFont> ResourceManager::getFont(const str &rid)
	{
        return get_or_default(backend::ttfontFactory(), m_private->m_fonts, rid);
    }

	sptr<scene::Texture> ResourceManager::getTexture(const str &rid)
	{
        return get_or_default(backend::textureFactory(), m_private->m_textures, rid);
	}

    sptr<scene::Shader> ResourceManager::getShader(const str &rid)
    {
        return get_or_default(backend::shaderFactory(), m_private->m_shaders, rid);
    }

    sptr<scene::TTFont> ResourceManager::loadFont(const str & rid, const str & fileName)
    {
        return get_or_add(backend::ttfontFactory(), m_private->m_fonts, rid, fileName);
    }
    sptr<scene::Texture> ResourceManager::loadTexture(const str & rid, const str & fileName)
    {
        return get_or_add(backend::textureFactory(), m_private->m_textures, rid, fileName);
    }
    sptr<scene::Shader> ResourceManager::loadShader(const str & rid, const str & fileName)
    {
        return get_or_add(backend::shaderFactory(), m_private->m_shaders, rid, fileName);
    }
}
