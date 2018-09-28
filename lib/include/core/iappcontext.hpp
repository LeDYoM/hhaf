#pragma once

#ifndef LIB_IAPPCONTEXT_INTERFACE_INCLUDE_HPP
#define LIB_IAPPCONTEXT_INTERFACE_INCLUDE_HPP

#include <mtypes/include/types.hpp>
#include <mtypes/include/str.hpp>

namespace lib::core
{
    /** This class is an interface that the user can use to set different properties of your app.
    * The host will take care of store and use them when necessary.
    */
    class IAppContext
    {
    public:
        /** 
        * Set the name of the application.
        */
        virtual void setApplicationName(str appName) = 0;

        /*
        * Set the major version of the application.
        */ 
        virtual void setApplicationVersion(size_type version) = 0;

        /**
        * Set the minor version of the application.
        */
        virtual void setApplicationSubVersion(size_type subversion) = 0;

        /**
        * Set the patch version of the application.
        */
        virtual void setApplicationPatch(size_type patch) = 0;

        /**
        * Set a property you want to communicate to the host.
        */
        virtual void setProperty(str prop_name, str prop_value) = 0;
    };
}

#endif
