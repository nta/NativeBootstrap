/*
    Initial author: (https://github.com/)Convery
    License: LGPL 3.0
    Started: 2016-3-05
    Notes:
        Compiletime hashing of strings.
        Runtime hashing of general data.
*/

#pragma once
#include <stdint.h>

// FNV1 constants.
constexpr uint32_t FNV1_Prime_32 = 16777619u;
constexpr uint64_t FNV1_Prime_64 = 1099511628211u;
constexpr uint32_t FNV1_Offset_32 = 2166136261u;
constexpr uint64_t FNV1_Offset_64 = 14695981039346656037u;
constexpr size_t FNV1_Prime_fast = (sizeof(size_t) == sizeof(uint64_t) ? FNV1_Prime_64 : FNV1_Prime_32);
constexpr size_t FNV1_Offset_fast = (sizeof(size_t) == sizeof(uint64_t) ? FNV1_Offset_64 : FNV1_Offset_32);

// FNV1 compiletime hashing.
constexpr uint32_t FNV1_Compiletime_32(const char *String, uint32_t LastValue = FNV1_Offset_32)
{
    return *String ? FNV1_Compiletime_32(String + 1, (LastValue * FNV1_Prime_32) ^ *String) : LastValue;
};
constexpr uint64_t FNV1_Compiletime_64(const char *String, uint64_t LastValue = FNV1_Offset_64)
{
    return *String ? FNV1_Compiletime_64(String + 1, (LastValue * FNV1_Prime_64) ^ *String) : LastValue;
};
constexpr uint32_t FNV1a_Compiletime_32(const char *String, uint32_t LastValue = FNV1_Offset_32)
{
    return *String ? FNV1a_Compiletime_32(String + 1, (*String ^ LastValue) * FNV1_Prime_32) : LastValue;
};
constexpr uint64_t FNV1a_Compiletime_64(const char *String, uint64_t LastValue = FNV1_Offset_64)
{
    return *String ? FNV1a_Compiletime_64(String + 1, (*String ^ LastValue) * FNV1_Prime_64) : LastValue;
};
constexpr size_t FNV1_Compiletime_fast(const char *String, size_t LastValue = FNV1_Offset_fast)
{
    return *String ? FNV1_Compiletime_fast(String + 1, (LastValue * FNV1_Prime_fast) ^ *String) : LastValue;
};
constexpr size_t FNV1a_Compiletime_fast(const char *String, size_t LastValue = FNV1_Offset_fast)
{
    return *String ? FNV1a_Compiletime_fast(String + 1, (*String ^ LastValue) * FNV1_Prime_fast) : LastValue;
};

// FNV1 runtime hashing.
inline uint32_t FNV1_Runtime_32(void *Data, size_t Length)
{
    uint32_t Hash = FNV1_Offset_32;

    for (size_t i = 0; i < Length; ++i)
    {
        Hash *= FNV1_Prime_32;
        Hash ^= ((uint8_t *)Data)[i];
    }

    return Hash;
};
inline uint64_t FNV1_Runtime_64(void *Data, size_t Length)
{
    uint64_t Hash = FNV1_Offset_64;

    for (size_t i = 0; i < Length; ++i)
    {
        Hash *= FNV1_Prime_64;
        Hash ^= ((uint8_t *)Data)[i];
    }

    return Hash;
};
inline size_t FNV1_Runtime_fast(void *Data, size_t Length)
{
    size_t Hash = FNV1_Offset_fast;

    for (size_t i = 0; i < Length; ++i)
    {
        Hash *= FNV1_Prime_fast;
        Hash ^= ((uint8_t *)Data)[i];
    }

    return Hash;
};
inline uint32_t FNV1a_Runtime_32(void *Data, size_t Length)
{
    uint32_t Hash = FNV1_Offset_32;

    for (size_t i = 0; i < Length; ++i)
    {
        Hash ^= ((uint8_t *)Data)[i];
        Hash *= FNV1_Prime_32;
    }

    return Hash;
};
inline uint64_t FNV1a_Runtime_64(void *Data, size_t Length)
{
    uint64_t Hash = FNV1_Offset_64;

    for (size_t i = 0; i < Length; ++i)
    {
        Hash ^= ((uint8_t *)Data)[i];
        Hash *= FNV1_Prime_64;
    }

    return Hash;
};
inline size_t FNV1a_Runtime_fast(void *Data, size_t Length)
{
    size_t Hash = FNV1_Offset_fast;

    for (size_t i = 0; i < Length; ++i)
    {
        Hash ^= ((uint8_t *)Data)[i];
        Hash *= FNV1_Prime_fast;
    }

    return Hash;
};
