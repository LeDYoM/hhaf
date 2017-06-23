#pragma once

#ifndef MTYPES_EXPORT_H
#define MTYPES_EXPORT_H

#ifdef mtypes_EXPORTS
        /* We are building this library */
#      define MTYPES_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define MTYPES_EXPORT __declspec(dllimport)
#    endif


#endif
