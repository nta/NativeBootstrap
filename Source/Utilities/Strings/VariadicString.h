/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-05
    Notes:
        Create a string from variadic arguments.
        const char *String = va("%i", 42);
        String == "42"
*/

#pragma once

const char *va(const char *fmt, ...);
const char *va_small(const char *fmt, ...);
const char *va_large(const char *fmt, ...);
