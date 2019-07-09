#pragma once

#ifndef LIB_ZOPERPROGRAMCONTROLLER_HPP
#define LIB_ZOPERPROGRAMCONTROLLER_HPP

#include <lib/include/iapp.hpp>
#include <mtypes/include/types.hpp>

namespace zoper
{
    using namespace lib;
    struct GameSharedData;
    class KeyMapping;

    class ZoperProgramController : public IApp
    {
    public:
        ZoperProgramController();
        virtual ~ZoperProgramController();

        void onInit() override;
        void onFinish() override;

        u16 getVersion() const noexcept override;
        u16 getSubVersion() const noexcept override;
        u16 getPatch() const noexcept override;
        str getName() const noexcept override;

        sptr<GameSharedData> gameSharedData;
        uptr<KeyMapping> keyMapping;
    };
}

#endif