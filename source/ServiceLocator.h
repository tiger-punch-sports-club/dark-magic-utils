#pragma once
#include <unordered_map>
#include <assert.h>
#include "CompileTimeHash.h"
#include "TypeId.h"

namespace DarkMagic
{
    // ********************************
    // Service locator
    // ********************************
    struct FServiceLocator
    {
        std::unordered_map<uint32_t, void*> Services;

        template <typename T>
        T* Get();

        template <typename T>
        void Set(T* Service);

        template <typename T>
        void Remove();
    };

    template <typename T>
    T* FServiceLocator::Get()
    {
        const FHashFnv1a Hash = HashData(typeid(T).name());
        return static_cast<T*>(Services.at(Hash.Value));
    }

    template <typename T>
    void FServiceLocator::Set(T* Service)
    {
        const FHashFnv1a Hash = HashData(typeid(T).name());
        assert(Services[Hash.Value] == nullptr && "Service already exists!");
        Services[Hash.Value] = Service;
    }

    template <typename T>
    void FServiceLocator::Remove()
    {
        const FHashFnv1a Hash = HashData(typeid(T).name());
        assert(Services[Hash.Value] != nullptr && "Service does not exists!");
        Services[Hash.Value] = nullptr;
    }
}
