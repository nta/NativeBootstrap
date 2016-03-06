/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-05
    Notes:
        The simplest system we have to log events.
*/

#pragma once
#include <stdio.h>
#include <mutex>
#include "VariadicString.h"

// Easier to edit with a constant path.
constexpr const char *Filepath = "Plugins\\Logs\\Bootstrap.log";

// Open and close a file rather than flushing a static handle in case
// we have other tools that need write access.
inline void AppendToLogfile(const char *Message, const char *Prefix)
{
    FILE *Filehandle;
    static std::mutex WriteMutex;

    WriteMutex.lock();
    {
        if (0 == fopen_s(&Filehandle, Filepath, "a"))
        {
            fputs(va("[%-7s] ", Prefix), Filehandle);
            fputs(Message, Filehandle);
            fputs("\n", Filehandle);
            fclose(Filehandle);
        }

#ifdef DEBUGTOSTREAM
        // Duplicate the message to stdout.
        {
            fputs(va("[%-7s] ", Prefix), stdout);
            fputs(Message, stdout);
            fputs("\n", stdout);
        }
#endif
    }
    WriteMutex.unlock();
}
inline void DeleteLogfile()
{
    std::remove(Filepath);
}
