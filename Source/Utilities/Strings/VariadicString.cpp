/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-05
    Notes:
        Create a string from variadic arguments.
        const char *String = va("%i", 42);
        String == "42"
*/

#include <mutex>
#include <stdarg.h>
#include "VariadicString.h"

// Buffer sizes.
#define BUFFER_SIZE 1024
#define SMALLBUFFER_SIZE 8
#define LARGEBUFFER_SIZE 2

// Store the strings in longer living buffers.
char SmallVABuffer[SMALLBUFFER_SIZE][BUFFER_SIZE / SMALLBUFFER_SIZE];
char LargeVABuffer[LARGEBUFFER_SIZE][BUFFER_SIZE / LARGEBUFFER_SIZE];
uint32_t SmallIndex = 0;
uint32_t LargeIndex = 0;

// Global lock to prevent two calls from using the same index.
std::mutex IndexGuard;

const char *va(const char *fmt, ...)
{
    va_list VarArgs;
    int32_t StringLength = 0;
    char DestinationBuffer[BUFFER_SIZE / LARGEBUFFER_SIZE]{};

    // Create a temporary string from the arguments.
    va_start(VarArgs, fmt);
    StringLength = _vsnprintf_s(DestinationBuffer, BUFFER_SIZE / LARGEBUFFER_SIZE, _TRUNCATE, fmt, VarArgs);
    va_end(VarArgs);

    // Send the string to permanent storage.
    if (StringLength > SMALLBUFFER_SIZE)
        return va_large(DestinationBuffer);
    else
        return va_small(DestinationBuffer);
}
const char *va_small(const char *fmt, ...)
{
    va_list VarArgs;
    char *DestinationBuffer = nullptr;

    // Safeguard the index.
    IndexGuard.lock();
    {
        // Clear any old data that resides in the buffer.
        DestinationBuffer = &SmallVABuffer[SmallIndex][0];
        memset(DestinationBuffer, 0, BUFFER_SIZE / SMALLBUFFER_SIZE);

        // Update the index for the next write.
        SmallIndex = (SmallIndex + 1) % SMALLBUFFER_SIZE;
    }
    IndexGuard.unlock();

    // Create the string from the arguments.
    va_start(VarArgs, fmt);
    _vsnprintf_s(DestinationBuffer, BUFFER_SIZE / SMALLBUFFER_SIZE, _TRUNCATE, fmt, VarArgs);
    va_end(VarArgs);

    return DestinationBuffer;
}
const char *va_large(const char *fmt, ...)
{
    va_list VarArgs;
    char *DestinationBuffer = nullptr;

    // Safeguard the index.
    IndexGuard.lock();
    {
        // Clear any old data that resides in the buffer.
        DestinationBuffer = &LargeVABuffer[LargeIndex][0];
        memset(DestinationBuffer, 0, BUFFER_SIZE / LARGEBUFFER_SIZE);

        // Update the index for the next write.
        LargeIndex = (LargeIndex + 1) % LARGEBUFFER_SIZE;
    }
    IndexGuard.unlock();

    // Create the string from the arguments.
    va_start(VarArgs, fmt);
    _vsnprintf_s(DestinationBuffer, BUFFER_SIZE / LARGEBUFFER_SIZE, _TRUNCATE, fmt, VarArgs);
    va_end(VarArgs);

    return DestinationBuffer;
}
