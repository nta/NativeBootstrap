/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-5
    Notes:
        Library entrypoint.
*/

#include <Macros.h>
#include <Bootstrap\Entrypointreplacement.h>

#ifndef _WIN32
void __attribute__ ((constructor)) DllMain(void)
{
    // Clean the logfile so we only save this session.
    DeleteLogfile();

    // Install the entrypoint callback.
    InstallCallback();
}
#else
#include <Windows.h>

BOOLEAN WINAPI DllMain(HINSTANCE hDllHandle, DWORD nReason, LPVOID Reserved)
{
    switch (nReason)
    {
    case DLL_PROCESS_ATTACH:
        // Rather not handle all thread updates.
        DisableThreadLibraryCalls(hDllHandle);

        // Clean the logfile so we only save this session.
        DeleteLogfile();

        // Install the entrypoint callback.
        InstallCallback();
        break;

    case DLL_PROCESS_DETACH:
        break;
    }

    return TRUE;
}
#endif
