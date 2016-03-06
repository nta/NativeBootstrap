/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-6
    Notes:
        1. Enumerate extension files.
        2. Load them into process memory.
        3. Call onInitialisationStart for each.
*/

#pragma once
#include <Macros.h>

// Load and unload the extensions.
void LoadExtensions();
void UnloadExtensions();

// Exported post initialization caller.
extern "C" EXPORT_ATTR void FinalizeExtensions();
