/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-05
    Notes:
        C style preprocessor macros for common functions.
*/

#pragma once
#include "Defines.h"
#include "Utilities\All.h"

// Debug information.
#ifdef NDEBUG
#define PrintFunction()
#define DebugPrint(string)
#define InfoPrint(string)
#else
#define PrintFunction() AppendToLogfile(__FUNCTION__, "Call to")
#define DebugPrint(string) AppendToLogfile(string, "Debug")
#define InfoPrint(string) AppendToLogfile(string, "Info")
#define NetworkPrint(string) AppendToLogfile(string, "Network")
#endif
