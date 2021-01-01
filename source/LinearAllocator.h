#pragma once

#include <cassert>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

namespace DarkMagic
{
    // ********************************
    // ReAllocSafe
    // ******************************** 
    inline void* ReAllocSafe(void* Memory, uint32_t OldSize, uint32_t NewSize)
    {
        void* Result = realloc(Memory, NewSize);

        if(Result == nullptr)
        {
            Result = malloc(NewSize);
            memset(Result, 0, NewSize);
            memcpy(Result, Memory, OldSize);
            free(Memory);
        }
        else if(Memory == nullptr)
        {
            memset(Result, 0, NewSize);
        }

        return Result;
    }

    // ********************************
    // LinearAllocator
    // ******************************** 
    struct FLinearAllocator
    {
        void* Memory;
        uint32_t MemorySize;
        uint8_t* CurrentPointer;

        void Init(uint32_t Size);
        void Destroy();
        void* Alloc(uint32_t Size);
        void Reset();
    };

    inline void FLinearAllocator::Init(uint32_t Size)
    {
        Memory = malloc(Size);
        MemorySize = Size;
        CurrentPointer = static_cast<uint8_t*>(Memory);
    }

    inline void FLinearAllocator::Destroy()
    {
        free(Memory);
        Memory = nullptr;
        MemorySize = 0;
        CurrentPointer = nullptr;
    }

    inline void* FLinearAllocator::Alloc(uint32_t Size)
    {
        assert(MemorySize - (CurrentPointer - Memory) >= Size && "LinearAllocator ran out of memory.");

        void* Current = CurrentPointer;
        CurrentPointer += Size;
        return Current;
    }

    inline void FLinearAllocator::Reset()
    {
        CurrentPointer = static_cast<uint8_t*>(Memory);
    }

    // ********************************
    // TypedLinearAllocator
    // ******************************** 
    template <typename T>
    struct TLinearAllocator
    {
        FLinearAllocator Allocator;

        void Init(uint32_t Count);
        void Destroy();
        T* Alloc();
        void Reset();
    };

    template <typename T>
    void TLinearAllocator<T>::Init(uint32_t Count)
    {
        Allocator.Init(sizeof(T) * Count);
    }

    template <typename T>
    void TLinearAllocator<T>::Destroy()
    {
        Allocator.Destroy();
    }

    template <typename T>
    T* TLinearAllocator<T>::Alloc()
    {
        return static_cast<T*>(Allocator.Alloc(sizeof(T)));
    }

    template <typename T>
    void TLinearAllocator<T>::Reset()
    {
        Allocator.Reset();
    }
}
