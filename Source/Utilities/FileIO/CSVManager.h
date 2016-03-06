/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-05
    Notes:
        CSV reading and writing.
*/

#pragma once
#include <string>
#include <vector>

struct CSVManager
{
    std::vector<std::vector<std::string>> EntryBuffer;

    bool ReadFile(const char *Filename);
    bool WriteFile(const char *Filename);
    std::string GetEntry(size_t Row, size_t Col);
};
