#pragma once

#ifndef LIB_ZOPERPROGRAMCONTROLLER_HPP
#define LIB_ZOPERPROGRAMCONTROLLER_HPP

#include <lib/include/iapp.hpp>
#include <mtypes/include/types.hpp>

namespace zoper
{
    struct GameSharedData;
    class KeyMapping;

    class ZoperProgramController : public lib::IApp
    {
    public:
        ZoperProgramController();
        ~ZoperProgramController() override;

        void onInit() override;
        void onFinish() override;

        lib::u16 getVersion() const noexcept override;
        lib::u16 getSubVersion() const noexcept override;
        lib::u16 getPatch() const noexcept override;
        lib::str getName() const noexcept override;

        lib::sptr<GameSharedData> gameSharedData;
        lib::uptr<KeyMapping> keyMapping;

        void importGameSharedData(lib::sptr<GameSharedData>& rhs)
        {
            rhs = gameSharedData;
        }
    };
}

#endif