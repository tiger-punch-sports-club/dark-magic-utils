#pragma once
#include <stdint.h>

namespace DarkMagic
{
    // *****************
    // CompileTimeHash (FNV v1a)
    // *****************
    struct FHashFnv1a
    {
        uint32_t Value;
    };

    namespace Fnv1aHashing
    {
        static constexpr uint32_t Offset = 2166136261u;
        static constexpr uint32_t Prime = 16777619u;
    };

    constexpr uint32_t CompileTimeHashHelper(uint32_t Partial, const char* Str)
    {
        return Str[0] == 0 ? Partial : CompileTimeHashHelper((Partial ^ Str[0]) * Fnv1aHashing::Prime, Str + 1);
    }

    constexpr FHashFnv1a HashData(const char* Input)
    {
        return FHashFnv1a{ CompileTimeHashHelper(Fnv1aHashing::Offset, Input) };
    }
}
