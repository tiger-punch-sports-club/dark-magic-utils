#pragma once

// ********************************
// ScopedPointer
// ********************************

template <typename T>
class TScopedPointer
{
public:

    explicit TScopedPointer(T* Pointer)
        : Pointer(Pointer)
    {
    }

    T* operator->()
    {
        return Pointer;
    }

    ~TScopedPointer()
    {
        delete Pointer;
    }

private:
    T* Pointer;
};
