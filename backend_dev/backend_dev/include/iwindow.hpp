#pragma once

#ifndef LIB_BACKEND_IWINDOW_INCLUDE_HPP
#define LIB_BACKEND_IWINDOW_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib::backend
{
    class IRenderTarget;
    class IInputDriver;

    class IWindow
    {
    public:

        virtual ~IWindow() {}

        virtual bool createWindow(const unsigned int,
            const unsigned int* const) = 0;
        virtual bool setActive(const bool activate) = 0;

        virtual bool processEvents() = 0;

        virtual void display() = 0;
        virtual void setWindowTitle(str newTitle) = 0;
        virtual void closeWindow() = 0;

        virtual IRenderTarget *renderTarget() = 0;
        virtual IInputDriver *inputDriver() = 0;
    };

    class IWindowProviderInfo
    {
    public:
        virtual const str info() = 0;
        virtual ~IWindowProviderInfo() {}
    };
}

#endif
