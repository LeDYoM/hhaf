#pragma once

#ifndef LFPROPERTIES_EXPORT_H
#define LFPROPERTIES_EXPORT_H

#ifdef lfproperties_EXPORTS
        /* We are building this library */
#      define LFPROPERTIES_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define LFPROPERTIES_EXPORT __declspec(dllimport)
#    endif


#endif
