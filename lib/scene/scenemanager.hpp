#pragma once

#ifndef LIB_SCENE_SCENEMANAGER_INCLUDE_HPP
#define LIB_SCENE_SCENEMANAGER_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>
#include <mtypes/include/properties.hpp>
#include <mtypes/include/function.hpp>
#include <lib/scene/components/componentcontainer.hpp>
#include <lib/scene/scene.hpp>
#include <lib/scene/scenecontroller.hpp>

#include <lib/system/appservice.hpp>
#include <lib/include/resources/iresourceretriever.hpp>

namespace lib::scene
{
    class SceneManager : public HostedAppService
    {
    public:
        SceneManager(core::SystemProvider &system_provider);
        ~SceneManager();

        void start();
        void update();
        void finish();

        IResourceRetriever &resources();

        Rectf32 viewPort() const noexcept;
        void setViewPort(const Rectf32& vp) noexcept;
        Rectf32 viewRect() const noexcept;
        void setViewRect(const Rectf32& vr) noexcept;

        inline const sptr<SceneController> &sceneController() const
            noexcept { return scene_controller_; }

        inline sptr<SceneController> &sceneController() 
            noexcept { return scene_controller_; }

    private:
        ComponentContainer m_componentContainer;
        sptr<SceneController> scene_controller_;
        SceneDirectorType scene_director_;
    };
}

#endif
