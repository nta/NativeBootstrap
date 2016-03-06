/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-05
    Notes:
        General defines for our configuration.
*/

#pragma once

// VS2015 no longer defines NDEBUG in release mode.
#ifdef _MSC_BUILD
#ifndef _DEBUG
#define NDEBUG
#endif
#endif

// Platform specific export attribute.
#ifdef __linux__
#define EXPORT_ATTR __attribute__((visibility("default")))
#define IMPORT_ATTR
#elif _WIN32
#define EXPORT_ATTR __declspec(dllexport)
#define IMPORT_ATTR __declspec(dllimport)
#else
#define EXPORT_ATTR
#define IMPORT_ATTR
#pragma warning Unknown dynamic link import/export semantics.
#endif

// Ignore warnings about constant integers overflowing (int32_t checks for uint32_t values).
#pragma warning(disable: 4307)

// Ignore warnings about empty switch cases as they occur in the API.
#pragma warning(disable: 4065)

// Build version.
#define VERSIONSTRING "0.1"

// Duplicate the debug output to stdout.
#define DEBUGTOSTREAM

// Windows API defines.
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

