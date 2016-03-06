/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-6
    Notes:
        The replacement in PE files.
*/

#ifdef _WIN32

#include <Macros.h>
#include <Windows.h>
#include "Entrypointreplacement.h"

// Host information.
char OriginalCode[20];
size_t OriginalEP;

// Make the application writable.
bool Unprotectmodule()
{
    HMODULE Module = GetModuleHandleA(NULL);
    if (!Module) return false;

    PIMAGE_DOS_HEADER DOSHeader = (PIMAGE_DOS_HEADER)Module;
    PIMAGE_NT_HEADERS NTHeader = (PIMAGE_NT_HEADERS)((DWORD_PTR)Module + DOSHeader->e_lfanew);
    SIZE_T Size = NTHeader->OptionalHeader.SizeOfImage;
    DWORD Original = 0;

    return NULL != VirtualProtect((void *)Module, Size, PAGE_EXECUTE_READWRITE, &Original);
}

// Read the applications entrypoint address.
size_t GrabEntrypoint()
{
    HMODULE Module = GetModuleHandleA(NULL);
    if (!Module) return 0;

    PIMAGE_DOS_HEADER DOSHeader = (PIMAGE_DOS_HEADER)Module;
    PIMAGE_NT_HEADERS NTHeader = (PIMAGE_NT_HEADERS)((DWORD_PTR)Module + DOSHeader->e_lfanew);

    return (size_t)((DWORD_PTR)Module + NTHeader->OptionalHeader.AddressOfEntryPoint);
}

// Install the callback and the callback itself.
void BootstrapCallback()
{
    PrintFunction();

    /*
        TODO(Convery):
        Load extensions.
    */

    // Restore the entrypoint data.
    std::memcpy((void *)OriginalEP, OriginalCode, 20);

    // Continue execution at the original entrypoint.
    __asm jmp OriginalEP;
}
void InstallCallback()
{
    // Sanity checking, maybe we're in an ELF file?
    if (!Unprotectmodule() || (OriginalEP = GrabEntrypoint()) == 0)
    {
        DebugPrint("The bootstrapper could not access the host applications image.");
        return;
    }

    // Backup the entrypoint.
    std::memcpy(OriginalCode, (void *)OriginalEP, 20);

    // Write a jump to the entrypoint.
#ifdef _WIN64
    *(uint8_t *)(OriginalEP + 0) = 0x48;                   // mov
    *(uint8_t *)(OriginalEP + 1) = 0xB8;                   // rax
    *(size_t *)(OriginalEP + 2) = (size_t)BootstrapCallback;
    *(uint8_t *)(OriginalEP + 10) = 0xFF;                  // jmp reg
    *(uint8_t *)(OriginalEP + 11) = 0xE0;                  // rax
#else
    *(uint8_t *)(OriginalEP + 0) = 0xE9;                   // jmp
    *(size_t *)(OriginalEP + 1) = ((size_t)BootstrapCallback - (OriginalEP + 5));
#endif
}

#endif // _WIN32
