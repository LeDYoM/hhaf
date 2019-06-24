#pragma once

#ifndef LIB_CORE_SYSTEM_RENDERSYSTEM_INCLUDE_HPP
#define LIB_CORE_SYSTEM_RENDERSYSTEM_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <lib/system/appservice.hpp>

namespace lib::scene
{
    class RenderData;
}

namespace lib::core
{
    /**
    * This system is intended to be the responsible of
    * priving the render data to the Backend render part.
    */
    class RenderSystem final : public HostedAppService
	{
	public:
        RenderSystem(core::SystemProvider &system_provider);
        ~RenderSystem() override;

        void update();

        void draw(const scene::RenderData &renderData);
        void clear();

    private:
        struct RenderSystemPrivate;
        uptr<RenderSystemPrivate> priv_;
    };
}

#endif
