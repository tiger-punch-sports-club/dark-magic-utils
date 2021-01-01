#pragma once

namespace DarkMagic
{
    // ********************************
    // Singleton pattern
    // ******************************** 
    template <typename T>
    class TSingleton
    {
    public:
        virtual ~TSingleton()
        {
        }
        static T* GetInstance();
    protected:
        TSingleton();
    };

    template <typename T>
    T* TSingleton<T>::GetInstance()
    {
        static T singleton{};
        return &singleton;
    }

    template <typename T>
    TSingleton<T>::TSingleton()
    {
    }
}
