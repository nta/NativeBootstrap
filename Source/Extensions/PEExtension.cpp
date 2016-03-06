/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-6
    Notes:
*/

#ifdef _WIN32

#include <Macros.h>
#include <Windows.h>
#include <Extensions\Interface.h>
#include <Extensions\ExtensionLoader.h>
#include <Bootstrap\Entrypointreplacement.h>

constexpr const char *Searchpath = (sizeof(void *) == 8 ? ".\\Plugins\\*.Ayria64" : ".\\Plugins\\*.Ayria32");
std::vector<IExtension> ExtensionList;

// Load and unload the extensions.
void LoadExtensions()
{
    WIN32_FIND_DATA FileData;
    HANDLE FileHandle;
    
    // Find the first extension.
    FileHandle = FindFirstFileA(Searchpath, &FileData);
    if (FileHandle == (void *)ERROR_INVALID_HANDLE || FileHandle == (void *)ERROR_INVALID_HANDLE)
    {
        DebugPrint("No extensions found.");
        return;
    }

    do
    {
        // Load the extensions into process memory.
        HMODULE Library = LoadLibraryA((".\\Plugins\\" + std::string(FileData.cFileName)).c_str());

        if (Library)
        {
            IExtension Extension;
            strncpy_s(Extension.Name, 65, (".\\Plugins\\" + std::string(FileData.cFileName)).c_str(), 64);
            Extension.onExtensionUnloading = (void (__cdecl *)(void))GetProcAddress(Library, "onExtensionUnloading");
            Extension.onInitializationStart = (void (__cdecl *)(void))GetProcAddress(Library, "onInitializationStart");
            Extension.onInitializationComplete = (void (__cdecl *)(void))GetProcAddress(Library, "onInitializationComplete");
            Extension.onMessage =(void (__cdecl *)(uint32_t Message, ...)) GetProcAddress(Library, "onMessage");

            ExtensionList.push_back(Extension);
        }
    } while (FindNextFileA(FileHandle, &FileData));

    // Log the extensions we loaded.
    DebugPrint(va("Loaded %i extensions:", ExtensionList.size()));
    for each (IExtension Ext in ExtensionList)
    {
        if (Ext.onInitializationStart)
            Ext.onInitializationStart();
        DebugPrint(Ext.Name);
    }

    // Ensure that the extensions are properly unloaded.
    std::atexit(UnloadExtensions);
}
void UnloadExtensions()
{
    for each (IExtension Ext in ExtensionList)
    {
        if (Ext.onExtensionUnloading)
            Ext.onExtensionUnloading();
    }
}

// Exported post initialization caller.
extern "C" EXPORT_ATTR void FinalizeExtensions()
{
    static bool Finalized = false;
    if (Finalized) return;
    else Finalized = true;

    for each (IExtension Ext in ExtensionList)
    {
        if (Ext.onInitializationComplete)
            Ext.onInitializationComplete();
    }
}

#endif // _WIN32
