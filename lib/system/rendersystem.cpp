#include "rendersystem.hpp"
#include "systemprovider.hpp"
#include "window.hpp"
#include "timesystem.hpp"
#include "rendertarget.hpp"
#include <lib/resources/texture.hpp>
#include <lib/scene/renderdata.hpp>
#include <logger/include/log.hpp>
#include <lib/include/core/timer.hpp>

#include <mtypes/include/types.hpp>

namespace lib::core
{
    struct RenderSystem::RenderSystemPrivate final
    {
    };

    RenderSystem::RenderSystem(core::SystemProvider &system_provider)
		: HostedAppService{ system_provider }, priv_{ muptr<RenderSystemPrivate>() }
    {
        system_provider.parentWindow().renderTarget()->viewPort();
    }

    RenderSystem::~RenderSystem() = default;

    void RenderSystem::update()
    {
    }

    void RenderSystem::draw(const scene::RenderData & renderData)
    {
        systemProvider().parentWindow().renderTarget()->draw(renderData);
    }

    void RenderSystem::clear()
    {
        systemProvider().parentWindow().renderTarget()->clear();
    }

}
