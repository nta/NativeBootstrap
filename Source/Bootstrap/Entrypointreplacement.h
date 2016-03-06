/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-6
    Notes:
        1. Replace the host applications EP with our callback.
        2. Wait for the callback to be called.
        3. Initialize the extensions.
        4. Restore the host applications EP.
        5. Continue the host application as usual.
*/

#pragma once

// Install the callback and the callback itself.
void BootstrapCallback();
void InstallCallback();
