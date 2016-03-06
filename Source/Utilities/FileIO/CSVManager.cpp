/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-05
    Notes:
        CSV reading and writing.
*/

#include <stdio.h>
#include <Macros.h>
#include "CSVManager.h"

#ifdef _WIN32
char *strsep(char **String, const char *Delimiter)
{
    char *Start = *String;
    char *Part;

    Part = (Start != NULL) ? strpbrk(Start, Delimiter) : NULL;

    if (Part == NULL)
        *String = NULL;
    else
    {
        *Part = '\0';
        *String = Part + 1;
    }

    return Start;
}
#endif
bool CSVManager::ReadFile(const char *Filename)
{
    FILE *Filehandle{ nullptr };
    char *InputString = new char [1024]();
    size_t Linecount{ 0 };
    char *Tempstring{ nullptr };
    char *Backupstring = InputString;

    // Ensure that the file exists.
    if (0 != fopen_s(&Filehandle, Filename, "r"))
        return false;

    // For each string in the file.
    while (fgets(InputString, 1024, Filehandle))
    {
        // If the line is empty, skip.
        if (strlen(InputString) < 2)
            continue;

        // If the line is a comment, skip.
        if (*InputString == '#')
            continue;

        // Create a new row in the buffer.
        EntryBuffer.push_back(std::vector<std::string>());
        Linecount++;

        // Split the string into tokens.
        while (true)
        {
            // Get next token.
            Tempstring = strsep(&InputString, ",\n\0");

            // Add the token or quit.
            if (Tempstring != nullptr)
            {
                // Remove any spaces before the value.
                while (*Tempstring == ' ')
                    Tempstring++;

                // Append the token and a null string if it's the end of the line.
                EntryBuffer[Linecount - 1].push_back(Tempstring);
            }                
            else
                break;
        }

        // Clear the buffer.
        InputString = Backupstring;
        memset(InputString, 0, 1024);
    }

    delete[] InputString;
    fclose(Filehandle);
    return true;
}
bool CSVManager::WriteFile(const char *Filename)
{
    FILE *Filehandle{ nullptr };

    // Check that we have anything to write.
    if (EntryBuffer.size() == 0)
        return false;

    // Create the file.
    if (0 != fopen_s(&Filehandle, Filename, "w"))
        return false;

    // Create the header.
    fputs("# This file is generated via Ayrias CSV manager.\n", Filehandle);
    fputs("# Layout: ", Filehandle);
    for (size_t i = 0; i < EntryBuffer[0].size(); ++i)
        fputs(va(" %c,", 0x41 + i), Filehandle);
    fputs("\n\n", Filehandle);

    // For each row.
    for (auto Iterator = EntryBuffer.begin(); Iterator != EntryBuffer.end(); ++Iterator)
    {
        for (auto Iterator2 = Iterator->begin(); Iterator2 != Iterator->end(); ++Iterator2)
            fputs(va(" %s,", Iterator2->c_str()), Filehandle);
        fputs("\n", Filehandle);
    }

    fclose(Filehandle);
    return true;
}
std::string CSVManager::GetEntry(size_t Row, size_t Col)
{
    // Check rowcount.
    if (Row > EntryBuffer.size() - 1)
        return "";

    // Check colcount.
    if (Col > EntryBuffer[Row].size() - 1)
        return "";

    return EntryBuffer[Row][Col];
}
