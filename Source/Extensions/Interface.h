/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-6
    Notes:
        Extension data-representation.
*/

#pragma once
#include <stdint.h>

struct IExtension
{
    char Name[65]{};
    void(__cdecl *onExtensionUnloading)(void);
    void(__cdecl *onInitializationStart)(void);
    void(__cdecl *onInitializationComplete)(void);
    void(__cdecl *onMessage)(uint32_t Message, ...);
};
