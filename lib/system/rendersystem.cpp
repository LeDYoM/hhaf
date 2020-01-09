#include "rendersystem.hpp"
#include "systemprovider.hpp"
#include "window.hpp"
#include "timesystem.hpp"
#include "rendertarget.hpp"
#include <lib/resources/texture.hpp>
#include <lib/scene/renderdata.hpp>
#include <lib/include/liblog.hpp>
#include <lib/include/core/timepoint.hpp>

#include <mtypes/include/types.hpp>

namespace lib::sys
{
    struct RenderSystem::RenderSystemPrivate final
    {
        RenderSystemPrivate() {}
        ~RenderSystemPrivate() {}
    };

    RenderSystem::RenderSystem(sys::SystemProvider &system_provider)
        : HostedAppService{ system_provider }, priv_{ muptr<RenderSystemPrivate>() }
    {
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
